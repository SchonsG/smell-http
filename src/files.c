#include "files.h"

#include "responses.h"
#include <sys/socket.h>

#define CHUNK_SIZE 8192 // 8KB chunks

int stream_file_content(const char* file_name, int client_fd) {
    FILE *file_pointer = fopen(file_name, "rb");
    if (file_pointer == NULL) {
        perror("Error opening file");
        return -1;
    }

    send_start_file(client_fd);

    char buffer[CHUNK_SIZE];
    char chunk_header[32];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, file_pointer)) > 0) {
        snprintf(chunk_header, sizeof(chunk_header), "%zx\r\n", bytes_read);
        send_file(client_fd, chunk_header, buffer, bytes_read);
    }

    send_end_file(client_fd);
    fclose(file_pointer);
    return 0;
}
