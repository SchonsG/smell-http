#ifndef REQUESTS_H
#define REQUESTS_H

#include <string.h>
#include <stdlib.h>

typedef struct {
    char *method;
    char *path;
    char *version;
    char *body;
} http_request_t;

http_request_t *parse_http_request(char *request_data);

#endif