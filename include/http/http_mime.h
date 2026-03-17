#ifndef HTTP_MIME_H
#define HTTP_MIME_H

#include <string.h>
#include <stdlib.h>

void copy_mime(char* file_type, char* extension, char* mime);

void create_text_mime(char** file_type, char* extension);

void create_image_mime(char** file_type, char* extension);

void create_video_mime(char** file_type, char* extension);


#endif