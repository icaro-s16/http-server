#include "http/http_request_types.h"

struct Request* http_req_create(){
    struct Request* request = malloc(sizeof(struct Request));
    request->type = NULL;
    request->url = NULL;
    request->type = NULL; 
    return request;
}

void http_req_destroy(struct Request* request){
    if (request == NULL) return;
    if (request->type != NULL) free(request->type);
    if (request->url != NULL) free(request->url);
    if (request->connection != NULL) free(request->connection);
    free(request);
}