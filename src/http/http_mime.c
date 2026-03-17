#include "http/http_mime.h"

void copy_mime(char* file_type, char* extension, char* mime){
    strcpy(file_type, mime);
    strcat(file_type, extension);
}

void create_text_mime(char** file_type, char* extension){
    char* mime_text = "text/";
    char* char_set = "; charset=UTF-8";
    *file_type = calloc(strlen(extension) + strlen(mime_text) + strlen(char_set) + 1, sizeof(char));
    strcpy(*file_type, mime_text);  
    strcat(*file_type, extension);
    strcat(*file_type, char_set);
}

void create_image_mime(char** file_type, char* extension){
    char* mime_image = "image/";
    *file_type = calloc(strlen(extension) + strlen(mime_image) + 1, sizeof(char));
    copy_mime(*file_type, extension, mime_image);
}

void create_video_mime(char** file_type, char* extension){
    char* mime_image = "video/";
    *file_type = calloc(strlen(extension) + strlen(mime_image) + 1, sizeof(char));
    copy_mime(*file_type, extension, mime_image);
}
