#ifndef FS_UTILS_H
#define FS_UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct FileStats{
    char* extension;
    char* file_type;
};

struct FileStats* fs_stat_create(char* fileName);

size_t fs_get_file_size(FILE* file);

FILE* fs_open_public_file(char* url);

char* fs_read_all_content(FILE* file);

void fs_stat_destroy(struct FileStats* file_stats);

int fs_valid_extension(char* content);

#endif