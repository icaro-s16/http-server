#include "utils/fs_utils.h"

struct FileStats* fs_stat_create(char* fileName){
    struct FileStats* stats = malloc(sizeof(struct FileStats));
    stats->extension = NULL;
    stats->file_type = NULL;

    char* mime_text = "text/";
    char* mime_img = "image/";

    char* auxFileName = calloc(strlen(fileName) + 1, sizeof(char));
    strcpy(auxFileName, fileName);

    char* delimeter = strchr(auxFileName, '.');
    
    if (delimeter == NULL || fs_valid_extension(auxFileName) == -1){

        char* undef_type = "application/octet-stream";
        stats->file_type = calloc(strlen(undef_type) + 1, sizeof(char));
        strcpy(stats->file_type, undef_type);
        
        if(auxFileName != NULL) free(auxFileName);
        return stats;
    }
    delimeter[0] = '\0';
    char* extension = delimeter + 1;

    stats->extension = calloc(strlen(extension) + 1, sizeof(char));
    strcpy(stats->extension, extension);
    
    if (strcmp(extension, "jpeg") == 0 || strcmp(extension, "png") == 0 || strcmp(extension, "jpg") == 0 ){
        stats->file_type = calloc(strlen(extension) + strlen(mime_img) + 1, sizeof(char));
        strcpy(stats->file_type, mime_img);
    }else{
        stats->file_type = calloc(strlen(extension) + strlen(mime_text) + 1, sizeof(char));
        strcpy(stats->file_type, mime_text);  
    }

    strcpy(&stats->file_type[strlen(stats->file_type)], extension);
    if(auxFileName != NULL) free(auxFileName);



    return stats;
}

size_t fs_get_file_size(FILE* file){
    if (file == NULL) return 0;

    fseek(file, 0L, SEEK_SET);
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0L, SEEK_SET);
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

char* fs_read_all_content(FILE* file){
    if (file == NULL) return NULL;
    
    size_t file_size = fs_get_file_size(file);
    char* content = calloc(file_size + 1, sizeof(char));
    fread(content, sizeof(char), file_size, file);
    return content;
}

void fs_stat_destroy(struct FileStats* file_stats){
    if (file_stats == NULL) return;
    if (file_stats->extension != NULL) free(file_stats->extension);
    if (file_stats->file_type != NULL) free(file_stats->file_type);

    free(file_stats);
}

int fs_valid_extension(char* content){
    if (content == NULL) return -1;
    
    char* copy_content = calloc(strlen(content) + 1, sizeof(char));
    strcpy(copy_content, content);

    char* delimeter = strchr(copy_content, '.');

    if (delimeter == NULL) return -1;

    delimeter[0] = '\0';
    char* extension = delimeter + 1;

    if (strcmp(extension, "css") == 0) return 0;

    if (strcmp(extension, "html") == 0) return 0;

    if (strcmp(extension, "jpeg") == 0) return 0;

    if (strcmp(extension, "png") == 0) return 0;

    if (strcmp(extension, "jpg") == 0) return 0;

    return -1;
}