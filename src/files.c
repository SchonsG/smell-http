#include "files.h"

#define CHUNK_SIZE 8192 // 8KB chunks

int stream_file_content(const char* file_name, int client_fd) {
    FILE *file_pointer = fopen(file_name, "rb");
    if (file_pointer == NULL) {
        perror("Error opening file");
        return -1;
    }

    send_start_file_stream(client_fd);

    char buffer[CHUNK_SIZE];
    char chunk_header[32];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, file_pointer)) > 0) {
        snprintf(chunk_header, sizeof(chunk_header), "%zx\r\n", bytes_read);
        send_chunk(client_fd, chunk_header, buffer, bytes_read);
    }

    send_end_file_stream(client_fd);

    fclose(file_pointer);
    return 0;
}

int send_file_content(const char* file_name, int client_fd, CacheManager* cache) {
    char* file_cache = get_from_cache(cache->cache, cache->ht, file_name);

    if (file_cache) {
        send_file(client_fd, file_cache, strlen(file_cache));
        free(file_cache);
        return 0;
    }

    FILE* file_pointer = fopen(file_name, "rb");
    if (!file_pointer) {
        perror("Error opening file");
        return -1;
    }

    // Get file length
    fseek(file_pointer, 0, SEEK_END);
    size_t length = ftell(file_pointer);
    fseek(file_pointer, 0, SEEK_SET);

    // Allocate memory for file data
    char* file = malloc(length + 1);
    if (!file) {
        fclose(file_pointer);
        perror("Memory allocation failed");
        return -1;
    }

    size_t bytes_read = fread(file, 1, length, file_pointer);
    if (bytes_read != length) {
        free(file);
        perror("Error reading file");
        return -1;
    }
    
    file[length] = '\0'; // Null-terminate the string
    send_file(client_fd, file, strlen(file));

    insert_into_cache(cache->cache, cache->ht, file_name, file);

    fclose(file_pointer);
    return 0;
}

size_t get_file_length(const char* file_name) {
    FILE *file_pointer = fopen(file_name, "rb");
    if (file_pointer == NULL) {
        perror("Error opening file");
        return 0;
    }

    fseek(file_pointer, 0, SEEK_END);
    size_t length = ftell(file_pointer);
    fclose(file_pointer);

    return length;
}
