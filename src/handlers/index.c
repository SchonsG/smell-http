#include "handlers/index.h"

http_response_t *handle_index(http_request_t *request) {
    http_response_t *response = malloc(sizeof(http_response_t));
    if (!response) return NULL;

    memset(response, 0, sizeof(http_response_t));

    response->status_code = 200;
    response->status_text = "OK";
    response->content_type = "application/json";
    response->content_body= "";

    return response;
}
