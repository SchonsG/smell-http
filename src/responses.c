#include "responses.h"

#define MAX_RESPONSE_SIZE 262144

void send_response(int client_fd, http_response_t *response) {
    char *response_txt = malloc(MAX_RESPONSE_SIZE);

    snprintf(response_txt, 2048,
        "HTTP/1.1 %d %s\r\nContent-Type: %s\r\nContent-Length: %lu\r\n\r\n%s",
        response->status_code, response->status_text, response->content_type,
        strlen(response->content_body), response->content_body);

    send(client_fd, response_txt, strlen(response_txt), 0);
}

void send_start_file_stream(int client_fd) {
    const char *hdr =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/octet-stream\r\n"
        "Transfer-Encoding: chunked\r\n"
        "Connection: keep-alive\r\n"
        "\r\n";
    send(client_fd, hdr, strlen(hdr), 0);
}

void send_chunk(int client_fd, char buffer_header[], char buffer[], size_t bytes) {
    send(client_fd, buffer_header, strlen(buffer_header), 0);
    send(client_fd, buffer, bytes, 0);
    send(client_fd, "\r\n", 2, 0);
}

void send_end_file_stream(int client_fd) {
    send(client_fd, "0\r\n\r\n", 5, 0);
}

void send_file(int client_fd, char* buffer, size_t bytes) {
    char response_header[512];
    snprintf(response_header, sizeof(response_header),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/octet-stream\r\n"
        "Content-Length: %zu\r\n"
        "Connection: keep-alive\r\n"
        "\r\n", bytes);
    
    send(client_fd, response_header, strlen(response_header), 0);
    send(client_fd, buffer, bytes, 0);
}
