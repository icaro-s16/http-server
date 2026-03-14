#ifndef HTTP_ROUTER_H
#define HTTP_ROUTER_H

#include "http_req_handlers.h"
#include "http_res_builder.h"
#include "structures/hash_map.h"
#include "http_request_types.h"
#include <stdlib.h>
#include <string.h>

struct HashMap* http_init_req_router();

struct HashMap* http_init_res_router();

#endif