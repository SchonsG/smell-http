#include "requests.h"
#include "handlers/endpoints.h"

// Parse basic HTTP request
http_request_t *parse_http_request(char *request_data) {
    http_request_t *request = malloc(sizeof(http_request_t));
    if (!request) return NULL;

    memset(request, 0, sizeof(http_request_t));

    char *line = strdup(request_data);
    char *method = strtok(line, " ");
    char *path = strtok(NULL, " ");
    char *version = strtok(NULL, "\r\n");

    if (method) request->method = strdup(method);
    if (path) request->path = strdup(path);
    if (version) request->version = strdup(version);

    free(line);
    return request;
}
