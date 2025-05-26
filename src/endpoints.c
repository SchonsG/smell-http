#include "endpoints.h"

// Add a global variable for the file server directory
static char *g_file_server_dir = NULL;

// Add a function to set the file server directory
void set_file_server_directory(const char *dir) {
    g_file_server_dir = (char *)dir;
}

http_response_t *not_found(void) {
    http_response_t *response = malloc(sizeof(http_response_t));
    if (!response) return NULL;

    response->status_code = 404;
    response->status_text = "Not Found";
    response->content_type = "application/json";
    response->content_body = "";

    return response;
}

http_response_t *handle_index(void) {
    http_response_t *response = malloc(sizeof(http_response_t));
    if (!response) return NULL;

    memset(response, 0, sizeof(http_response_t));

    response->status_code = 200;
    response->status_text = "OK";
    response->content_type = "application/json";
    response->content_body= "";

    return response;
}

char *get_value_from_path(char *path, int start) {
    path += start;
    char *end = strchr(path, '/');
    int len = end ? (end - path) : strlen(path);

    char *result = malloc(len+1);
    if (!result) return NULL;

    strncpy(result, path, len);
    result[len] = '\0';

    return result;
}

http_response_t *handle_echo(http_request_t *request) {
    http_response_t *response = malloc(sizeof(http_response_t));
    if (!response) return NULL;

    memset(response, 0, sizeof(http_response_t));

    response->status_code = 200;
    response->status_text = "OK";
    response->content_type = "application/json";
    response->content_body = get_value_from_path(request->path, 6); // skip `/echo/`

    return response;
}

int handle_files(http_request_t *request, int client_id) {
    char *file_path = malloc(1024);
    char *file_name = get_value_from_path(request->path, 7); // skip `/files/`
    sprintf(file_path, "%s/%s", g_file_server_dir, file_name);

    int success = stream_file_content(file_path, client_id);
    if (!success) return -1;

    return 0;
}
