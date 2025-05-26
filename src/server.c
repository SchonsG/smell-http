#include "server.h"
#include "endpoints.h"

#define BUFFER_SIZE 4096

void handle_client_request(int client_fd) {
	char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes_received <= 0) close(client_fd);

	http_request_t *request = parse_http_request(buffer);
	route_http(request, client_fd);
	free(request);
}

// Print server startup information
void print_server_info(int port) {
    printf("HTTP Server running on port %d\n", port);
    printf("Available endpoints:\n");
    printf("  GET /files  		- File listing with chunked transfer encoding\n");
    printf("  GET /echo 		- Echo echo...\n");
	printf("  GET /*      		- 200 OK\n");
    printf("  GET /*      		- 404 page\n\n");
    printf("Test with:\n");
    printf("  curl http://localhost:%d/echo/hello\n", port);
    printf("  curl http://localhost:%d/files/foo\n\n", port);
}

int create_server_socket(int port) {
	int server_fd;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) {
		printf("Socket creation failed: %s...\n", strerror(errno));
		return 1;
	}
	
	struct sockaddr_in serv_addr = { .sin_family = AF_INET ,
									 .sin_port = htons(port),
									 .sin_addr = { htonl(INADDR_ANY) },
									};
	
	if (bind(server_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != 0) {
		printf("Bind failed: %s \n", strerror(errno));
		return 1;
	}
	
	int connection_backlog = 5;
	if (listen(server_fd, connection_backlog) != 0) {
		printf("Listen failed: %s \n", strerror(errno));
		return 1;
	}

	return server_fd;
}

void run_server(int port, char *file_server) {
	setbuf(stdout, NULL);
 	setbuf(stderr, NULL);

	set_file_server_directory(file_server);

	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	
	int server_fd = create_server_socket(port);
	print_server_info(port);

	printf("Waiting for a client to connect...\n");
	client_addr_len = sizeof(client_addr);

	while (1) {
		int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_addr_len);
		if (client_fd < 0) {
			puts("Error connecting...");
			continue;	
		}

		handle_client_request(client_fd);
	}

	close(server_fd);
}
