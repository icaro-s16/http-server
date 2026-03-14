#ifndef HTTP_REQUEST_TYPES_H
#define HTTP_REQUEST_TYPES_H

#include <stdlib.h>

struct Request{
    char* type;  
    char* url;  
    char* connection;
};

struct Request* http_req_create();

void http_req_destroy(struct Request* request);

#endif