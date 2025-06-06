#include "handlers/not_found.h"

http_response_t *not_found(void) {
    http_response_t *response = malloc(sizeof(http_response_t));
    if (!response) return NULL;

    response->status_code = 404;
    response->status_text = "Not Found";
    response->content_type = "application/json";
    response->content_body = "";

    return response;
}
