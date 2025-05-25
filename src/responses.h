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

#endif
