#include "http/http_router.h"

struct HashMap* http_init_req_router(){
    struct HashMap* http_map = hashmap_create("Request", &http_parse_request_line, sizeof(void(*)(char*, struct Request*)));
    hashmap_insert(http_map, "Connection", &http_parse_connection_header);
    
    return http_map;
    
};

struct HashMap* http_init_res_router(){
    struct HashMap* http_map = hashmap_create("GET", &http_handle_get_method, sizeof(struct String* (*) (struct Request*)));

    return http_map;
}