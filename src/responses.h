#ifndef RESPONSES_H
#define RESPONSES_H

#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status_code;
    char *status_text;
    char *content_type;
    char *content_body;
} http_response_t;

void send_response(int client_fd, http_response_t *response);

void send_start_file_stream(int client_fd);
void send_chunk(int client_fd, char buffer_header[], char buffer[], size_t bytes_read);
void send_end_file_stream(int client_fd);
void send_file(int client_fd, char* buffer, size_t bytes);

#endif
