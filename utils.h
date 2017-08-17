#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <libproc.h>
#include <unistd.h>

char *get_dir_name();
char *join_path(char *path1, char *path2);
FILE *smart_fopen(char *path, char *mode);

#endif
