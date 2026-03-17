#include "http/http_req_parser.h"

struct Request* http_parse_request(struct Bytes* uc_request, struct HashMap* hashMap){

    if (hashMap->sizeType != sizeof(void(*)(char*, struct Request*))) return NULL;
    
    char* c_request = calloc(uc_request->size + 1, sizeof(char));
    memcpy(c_request, uc_request->bytes, uc_request->size);


    char* save_pointer;
    struct Request* request = http_req_create();


    char* line = strtok_r(c_request, "\r\n", &save_pointer);
    while (line != NULL){
        char* delimeter = strchr(line, ':');
        if(delimeter != NULL){

            delimeter[0] = '\0';
            
            char* label = line;
            char* content = delimeter + 1;
            struct Pair* pair = hashmap_get(hashMap, label);
            struct Bytes* st_content = bt_create(content, strlen(content));
            if(pair != NULL){
                ((void(*)(char*, struct Request*))pair->value)(content, request);
            }
            bt_destroy(st_content);
        }
        line = strtok_r(NULL, "\r\n", &save_pointer);
    }

    free(c_request);

    if (strcmp(request->url, "/") == 0){
        char* default_file = "index.html";
        
        size_t url_size = strlen(request->url);
        size_t size =  strlen(request->url) + strlen(default_file) + 1 ;

        char* aux_pointer = realloc(request->url, size);
        if (aux_pointer != request->url){
            request->url = aux_pointer;
        }
        memset(&request->url[url_size], 0, size - url_size);

        strcat(request->url, default_file);
    }

    return request;
};