#include "routes.h"

void route_http(http_request_t *request, int client_id) {
    http_response_t *response = not_found();

    if (strcmp(request->path, "/") == 0)
        response = handle_index();

    if (strncmp(request->path, "/echo", 5) == 0)
        response = handle_echo(request);

    if (strncmp(request->path, "/files", 6) == 0)
        if (handle_files(request, client_id)) {
            // the response is handled by the files
            return;
        }

    send_response(client_id, response);
}
