#ifndef ROUTES_H
#define ROUTES_H

#include "endpoints.h"
#include "responses.h"
#include "requests.h"

void *route_http(http_request_t *request, int client_id);

#endif