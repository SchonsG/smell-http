#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include "../handlers/endpoints.h"
#include "responses.h"
#include "requests.h"
#include "routes.h"
#include "cache.h"

void handle_client_request(int client_fd, CacheManager* cache);
void print_server_info(int port);
int create_server_socket(int port);
void run_server(int port, char *file_server);

#endif // SERVER_H