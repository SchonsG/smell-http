#ifndef ROUTES_H
#define ROUTES_H

#include "handlers/endpoints.h"
#include "responses.h"
#include "requests.h"
#include "cache/cache.h"

void route_http(http_request_t *request, int client_id, CacheManager* cache);

#endif