#include "routes.h"

#define FILES_PATH "/files"

typedef struct {
    const char *method;
    const char *path;
    http_response_t* (*handler)(http_request_t *);
} Route;

const Route routes[] = {
    {"GET", "/echo", handle_echo},
    {"GET", "/", handle_index},
};

void route_http(http_request_t *request, int client_id, CacheManager* cache) {
    http_response_t *response = not_found();

    for (size_t i = 0; i < sizeof(routes) / sizeof(routes[0]); i++) {
        if (strcmp(request->method, routes[i].method) != 0) {
            continue;
        }
        if (strncmp(request->path, routes[i].path, strlen(routes[i].path)) != 0) {
            continue;
        }
        response = routes[i].handler(request);
        break;
    }

    if (strncmp(request->path, FILES_PATH, strlen(FILES_PATH)) == 0) {
        if (handle_files(request, client_id, cache)) {
            // the response is handled by the files
            return;
        }
    }

    send_response(client_id, response);
}
