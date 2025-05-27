#include "utils.h"

char *extract_path_segment(char *path) {
    char *end = strrchr(path, '/') + 1;
    int len = end ? (end - path) : strlen(path);
    return strndup(end, len);
}
