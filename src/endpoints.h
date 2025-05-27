#ifndef ENDPOINTS_H
#define ENDPOINTS_H

#include <stdlib.h>
#include <string.h>

#include "responses.h"
#include "requests.h"
#include "files.h"
#include "utils.h"

void set_file_server_directory(const char *dir);
char *get_echo_from_path(char *path);
http_response_t *not_found(void);
http_response_t *handle_index(void);
http_response_t *handle_echo(http_request_t *request);
int handle_files(http_request_t *request, int client_id);

#endif