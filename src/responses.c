#include "responses.h"

#define MAX_RESPONSE_SIZE 262144

void send_response(int client_fd, http_response_t *response) {
    char *response_txt = malloc(MAX_RESPONSE_SIZE);

    snprintf(response_txt, 2048,
        "HTTP/1.1 %d %s\r\nContent-Type: %s\r\nContent-Length: %lu\r\n\r\n%s",
        response->status_code, response->status_text, response->content_type,
        strlen(response->content_body), response->content_body);

    send(client_fd, response_txt, strlen(response_txt), 0);
}
