#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

#define PORT 4221

int main(int argc, char *argv[]) {
    int port = PORT;
    char *file_server = "";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file-directory") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: --file-directory requires a directory path\n");
                exit(EXIT_FAILURE);
            }
            i++;
            file_server = argv[i];
        }
        else if (strcmp(argv[i], "--port") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: --port requires a port number\n");
                exit(EXIT_FAILURE);
            }
            i++;
            int parsed_port = atoi(argv[i]);
            if (parsed_port <= 0 || parsed_port > 65535) {
                fprintf(stderr, "PORT out of valid range: %d\n", parsed_port);
                exit(EXIT_FAILURE);
            }
            port = parsed_port;
        }
    }


    printf("Starting HTTP Server on port %d...\n", port);
    printf("Serving files from directory: %s\n", file_server);

    printf("Starting HTTP Server with Chunked Transfer Encoding...\n\n");
    run_server(port, file_server);
}
