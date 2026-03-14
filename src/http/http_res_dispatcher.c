#include "http/http_res_dispatcher.h"

struct String* http_dispatch_request(struct HashMap* command_map, struct Packet* packet, struct Request* request){
    struct String* response = NULL; 


    if (command_map->sizeType != sizeof(struct String* (*) (struct Request*))) return response;
    
    if (request == NULL || command_map == NULL || packet == NULL) return NULL;

    struct Pair* pair = hashmap_get(command_map, request->type);
    if(pair != NULL){
        response = ((struct String* (*) (struct Request*))pair->value)(request);
    }

    return response;
}