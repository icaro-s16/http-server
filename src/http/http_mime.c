#include "http/http_mime.h"

void copy_mime(char* file_type, char* extension, char* mime){
    strcpy(file_type, mime);
    strcat(file_type, extension);
}

char* create_text_mime(char* extension){
    char* mime_text = "text/";
    char* char_set = "; charset=UTF-8";
    char* file_type = calloc(strlen(extension) + strlen(mime_text) + strlen(char_set) + 1, sizeof(char));
    strcpy(file_type, mime_text);  
    strcat(file_type, extension);
    strcat(file_type, char_set);
    return file_type;
}

char* create_image_mime(char* extension){
    char* mime_image = "image/";
    char* file_type = calloc(strlen(extension) + strlen(mime_image) + 1, sizeof(char));
    copy_mime(file_type, extension, mime_image);
    return file_type;
}

char* create_video_mime(char* extension){
    char* mime_image = "video/";
    char* file_type = calloc(strlen(extension) + strlen(mime_image) + 1, sizeof(char));
    copy_mime(file_type, extension, mime_image);
    return file_type;
}
