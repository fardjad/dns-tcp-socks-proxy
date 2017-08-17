#include "utils.h"

char *get_dir_name() {
    pid_t pid = getpid();
    char path[PROC_PIDPATHINFO_MAXSIZE];
    int len = proc_pidpath(pid, path, PROC_PIDPATHINFO_MAXSIZE * sizeof(char));
    if (len <= 0) {
        return NULL;
    }

    int slash_location = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (path[i] == '/') {
            slash_location = i;
            break;
        }
    }

    if (slash_location == 0) {
        // something's wrong
        return NULL;
    }

    char *dirname = (char *) malloc((slash_location + 1) * sizeof(char));
    strncpy(dirname, path, slash_location * sizeof(char));
    dirname[slash_location] = (char) 0;

    return dirname;
}

char *join_path(char *path1, char *path2) {
    int path1_len = strlen(path1);
    int path2_len = strlen(path2);

    int joined_path_len = path1_len + path2_len + 2; // +2 is for '/' and '\0'
    char *joined_path = (char *) malloc(joined_path_len * sizeof(char));
    strncpy(joined_path, path1, path1_len * sizeof(char));
    strncat(joined_path, "/", sizeof(char));
    strncat(joined_path, path2, path2_len * sizeof(char));

    return joined_path;
}

FILE *smart_fopen(char *path, char *mode) {
    FILE *f;
    // try opening the file (most likely from cwd)
    f = fopen(path, mode);
    if (!f) {
        // try opening the file from program directory
        char *full_path = join_path(get_dir_name(), path);
        f = fopen(full_path, mode);
    }
    return f;
}

