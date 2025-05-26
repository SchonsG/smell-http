#include <stdio.h>
#include <stdlib.h>
#include "server.h"

#define PORT 4221

int main(int argc, char *argv[]) {
    int port = PORT;
    char *file_server = "";

    for (int i = 1; i < argc; i ++) {
        if (strcmp(argv[i], "--file-directory") == 0) {
            i++;
            file_server = argv[i];
        } else {
            int port = atoi(argv[i]);
            if (port <= 0 || port > 65535) {
                fprintf(stderr, "PORT out of valid range: %d\n", port);
                exit(EXIT_FAILURE);
            }
        }
    }

    printf("Starting HTTP Server with Chunked Transfer Encoding...\n\n");
    run_server(port, file_server);
}
