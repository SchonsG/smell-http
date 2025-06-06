#include "handlers/endpoints.h"

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

http_response_t *handle_index(http_request_t *request) {
    http_response_t *response = malloc(sizeof(http_response_t));
    if (!response) return NULL;

    memset(response, 0, sizeof(http_response_t));

    response->status_code = 200;
    response->status_text = "OK";
    response->content_type = "application/json";
    response->content_body= "";

    return response;
}

http_response_t *handle_echo(http_request_t *request) {
    http_response_t *response = malloc(sizeof(http_response_t));
    if (!response) return NULL;

    memset(response, 0, sizeof(http_response_t));

    response->status_code = 200;
    response->status_text = "OK";
    response->content_type = "application/json";
    response->content_body = extract_path_segment(request->path); // skip `/echo/`

    return response;
}

int handle_files(http_request_t *request, int client_id, CacheManager* cache) {
    char *file_path = malloc(1024);
    char *file_name = extract_path_segment(request->path); // skip `/files/`
    sprintf(file_path, "%s/%s", g_file_server_dir, file_name);

    size_t f_length = get_file_length(file_path);

    if (f_length > 1024 * 1024 * 10) { // Limit to 10MB
        int success = stream_file_content(file_path, client_id);
        if (!success) return -1;
    } else {
        int success = send_file_content(file_path, client_id, cache);
        if (!success) return -1;
    }

    return 0;
}
