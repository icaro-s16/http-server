#ifndef HTTP_REQ_HANDLERS_H
#define HTTP_REQ_HANDLERS_H

#include "structures/d_string.h"
#include "http_request_types.h"
#include <string.h>
#include <stdlib.h>

void http_parse_connection_header(char* content, struct Request* request_st);

void http_parse_request_line(char* content, struct Request* request_st);

int http_is_header_complete(char* buffer);

#endif