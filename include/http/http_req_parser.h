#ifndef HTTP_REQ_PARSER_H
#define HTTP_REQ_PARSER_H

#include <string.h>
#include <stdlib.h>
#include "structures/d_string.h"
#include "structures/hash_map.h"
#include "http_request_types.h"

struct Request* http_parse_request(struct String* c_request, struct HashMap* hashMap);

#endif