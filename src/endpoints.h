#ifndef ENDPOINTS_H
#define ENDPOINTS_H

#include <stdlib.h>
#include <string.h>

#include "responses.h"
#include "requests.h"

char *get_echo_from_path(char *path);
http_response_t *not_found(void);
http_response_t *handle_echo(http_request_t *request);
http_response_t *handle_index(void);
// http_response_t *handle_files(void);

#endif