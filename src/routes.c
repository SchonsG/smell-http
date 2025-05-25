#include "routes.h"

void *route_http(http_request_t *request, int client_id) {
    if (strncmp(request->path, "/", 1) == 0) {
        http_response_t *response = handle_index();
        send_response(client_id, response);
    };

    if (strncmp(request->path, "/echo", 5) == 0) {
        http_response_t *response = handle_echo();
    }

    // if (strncmp(request->path, "/files", 6) == 0) return handle_files();
}
