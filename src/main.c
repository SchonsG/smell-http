#include <stdio.h>
#include <stdlib.h>
#include "server.h"

#define PORT 4221

int main(int argc, char *argv[]) {
    int port = PORT;
    
    if (argc > 1) {
        int port = atoi(argv[1]);

        if (port <= 0 || port > 65535) {
            fprintf(stderr, "PORT out of valid range: %d\n", port);
            exit(EXIT_FAILURE);
        }
    }

    printf("Starting HTTP Server with Chunked Transfer Encoding...\n");
    run_server(port);
}
