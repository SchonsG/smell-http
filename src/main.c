#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "../include/network/server.h"

#define PORT 4221
#define SERVER "/Users/gschons/Workspace/gschons/smell-http/files"

int main(int argc, char *argv[]) {
    int opt;
    int option_index = 0;

    int port = PORT;
    char *file_server = SERVER;

    struct option long_options[] = {
        {"directory", optional_argument, 0, 'd'},
        {"port", optional_argument, 0, 'p'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "d:p:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'd':
                file_server = optarg;
                break;
            case 'p':
                port = atoi(optarg);
                break;
        }
    }

    printf("Starting HTTP Server on port %d...\n", port);
    printf("Serving files from directory: %s\n", file_server);
    printf("Starting HTTP Server with Chunked Transfer Encoding...\n\n");

    run_server(port, file_server);
}
