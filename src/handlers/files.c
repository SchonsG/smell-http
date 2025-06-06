#include "handlers/files.h"

// Add a global variable for the file server directory
static char *g_file_server_dir = NULL;

// Add a function to set the file server directory
void set_file_server_directory(const char *dir) {
    g_file_server_dir = (char *)dir;
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
