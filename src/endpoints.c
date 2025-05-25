#include "endpoints.h"

http_response_t *handle_index(void) {
    http_response_t *response = malloc(sizeof(http_response_t));
    if (!response) return NULL;

    memset(response, 0, sizeof(http_response_t));

    response->status_code = 200;
    response->status_text = "OK";
    response->content_type = "application/json";
    response->content_body= "";

    return response;
}

char *get_echo_from_path(char *path) {
    path += 6; // skip the '/echo/'
    char *end = strchr(path, '/');
    int len = end ? (end - path) : strlen(path);

    char *result = malloc(len+1);
    if (!result) return NULL;

    strncpy(result, path, len);
    result[len] = '\0';

    return result;
}

http_response_t *handle_echo(http_request_t *request) {
    http_response_t *response = malloc(sizeof(http_response_t));
    if (!response) return NULL;

    memset(response, 0, sizeof(http_response_t));

    response->status_code = 200;
    response->status_text = "OK";
    response->content_type = "application/json";
    response->content_body = get_echo_from_path(request->path);

    return response;
}

// void handle_files(void) {}
