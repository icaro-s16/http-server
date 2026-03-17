#ifndef HTTP_MIME_H
#define HTTP_MIME_H

#include <string.h>
#include <stdlib.h>

void copy_mime(char* file_type, char* extension, char* mime);

char* create_text_mime(char* extension);

char* create_image_mime(char* extension);

char* create_video_mime(char* extension);


#endif