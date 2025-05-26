#include "files.h"

#include <sys/socket.h>

#define CHUNK_SIZE 8192 // 8KB chunks

int stream_file_content(const char* file_name, int client_fd) {
    FILE *file_pointer = fopen(file_name, "rb");
    if (file_pointer == NULL) {
        perror("Error opening file");
        return -1;
    }

    const char *hdr =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/octet-stream\r\n"
        "Transfer-Encoding: chunked\r\n"
        "Connection: keep-alive\r\n"
        "\r\n";
    send(client_fd, hdr, strlen(hdr), 0);

    char buffer[CHUNK_SIZE];
    char chunk_header[32];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, file_pointer)) > 0) {
        // Send chunk size in hex + CRLF
        snprintf(chunk_header, sizeof(chunk_header), "%zx\r\n", bytes_read);
        send(client_fd, chunk_header, strlen(chunk_header), 0);

        // Send chunk data + CRLF
        send(client_fd, buffer, bytes_read, 0);
        send(client_fd, "\r\n", 2, 0);
    }

    // End chunked tranfer
    send(client_fd, "0\r\n\r\n", 5, 0);
    fclose(file_pointer);
    return 0;
}

long get_file_size(const char* file_name) {
    FILE *file_pointer = fopen(file_name, "rb");
    if (file_pointer == NULL) return -1;
    
    fseek(file_pointer, 0, SEEK_END);
    long size = ftell(file_pointer);
    fclose(file_pointer);
    
    return size;
}
