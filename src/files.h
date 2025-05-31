#ifndef FILES_H
#define FILES_H

#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

#include "responses.h"
#include "cache.h"

int stream_file_content(const char* file_name, int client_socket);
int send_file_content(const char* file_name, int client_fd, CacheManager* cache);
size_t get_file_length(const char* file_name);

#endif