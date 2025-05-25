#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <string.h>

int stream_file_content(const char* file_name, int client_socket);
long get_file_size(const char* file_name);

#endif