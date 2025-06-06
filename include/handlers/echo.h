#ifndef ECHO_H
#define ECHO_H

#include <stdlib.h>

#include "utils/utils.h"
#include "responses.h"
#include "requests.h"

http_response_t *handle_echo(http_request_t *request);

#endif
