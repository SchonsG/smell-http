#ifndef FILES_H
#define FILES_H

#include <stdlib.h>

#include "cache/cache.h"
#include "utils/utils.h"
#include "responses.h"
#include "requests.h"
#include "files.h"

http_response_t *handle_echo(http_request_t *request);

void set_file_server_directory(const char *dir);
int handle_files(http_request_t *request, int client_id, CacheManager* cache);

#endif