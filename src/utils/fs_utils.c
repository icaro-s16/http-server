#include "utils/fs_utils.h"

struct FileStats* fs_stat_create(char* fileName, struct HashMap* mime_map){
    if (fileName == NULL ) return NULL;

    struct FileStats* stats = malloc(sizeof(struct FileStats));
    stats->extension = NULL;
    stats->file_type = NULL;

    struct Pair* pair = NULL;
    struct HashMap* mime_map = NULL;

    char* auxFileName = calloc(strlen(fileName) + 1, sizeof(char));
    strcpy(auxFileName, fileName);

    char* delimeter = strchr(auxFileName, '.');
    char* extension = NULL;

    if (delimeter != NULL) delimeter[0] = '\0';
    if (delimeter != NULL) {

        extension = delimeter + 1;

        stats->extension = calloc(strlen(extension) + 1, sizeof(char));
        strcpy(stats->extension, extension);
        
        mime_map = http_init_mime_router();
        pair = hashmap_get(mime_map, extension);
    }

    if(pair != NULL){
        
        stats->file_type = ((char*(*)(char*))pair->value)(extension);

    }else{
        char* undef_type = "application/octet-stream";
        stats->file_type = calloc(strlen(undef_type) + 1, sizeof(char));
        strcpy(stats->file_type, undef_type);
        
        if(auxFileName != NULL) free(auxFileName);
        return stats;

    }


    if(auxFileName != NULL) free(auxFileName);
    if(mime_map != NULL) hashmap_destroy(mime_map);
    return stats;
}

size_t fs_get_file_size(FILE* file){
    if (file == NULL) return 0;
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    return size;
}

FILE* fs_open_public_file(char* url){
    if (url == NULL || strlen(url) == 0) return NULL;
    char* default_dir = "public_http";
    size_t default_dir_size = strlen(default_dir);
    size_t total_size = strlen(url) + strlen(default_dir);

    char* path = calloc(total_size + 1, sizeof(char));
    strcpy(path, default_dir);
    strcat(path, url);

    FILE* file_fd = fopen(path, "rb");
    free(path);

    return file_fd;
}

unsigned char* fs_read_all_content(FILE* file){
    if (file == NULL) return NULL;
    
    size_t file_size = fs_get_file_size(file);
    unsigned char* content = calloc(file_size + 1, sizeof(unsigned char));
    fread(content, sizeof(unsigned char), file_size, file);
    return content;
}

void fs_stat_destroy(struct FileStats* file_stats){
    if (file_stats == NULL) return;
    if (file_stats->extension != NULL) free(file_stats->extension);
    if (file_stats->file_type != NULL) free(file_stats->file_type);

    free(file_stats);
}

