#ifndef INDEX_H
#define INDEX_H

#include <stdlib.h>

#include "responses.h"
#include "requests.h"

http_response_t *handle_index(http_request_t *request);

#endif