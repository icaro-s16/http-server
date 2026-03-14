#include "http/http_req_handlers.h"

void http_parse_request_line(char* content, struct Request* request_st){
    char* save_pointer;

    char* split_content = strtok_r(content, " ", &save_pointer);
    if(split_content == NULL) return;
    
    request_st->type = malloc(sizeof(char) * (strlen(split_content) + 1));
    strcpy(request_st->type, split_content);
    
    split_content = strtok_r(NULL, " ", &save_pointer);
    if(split_content == NULL) return;
    
    request_st->url = malloc(sizeof(char) * (strlen(split_content) + 1));
    strcpy(request_st->url, split_content);

}

void http_parse_connection_header(char* content, struct Request* request_st){
    char* save_pointer;

    char* split_content = strtok_r(content, " ", &save_pointer);
    if(split_content == NULL) return;
    request_st->connection = calloc(strlen(split_content) + 1, sizeof(char));
    strcpy(request_st->connection, split_content);

}

int http_is_header_complete(char* buffer){
    for(int i = 0; i < strlen(buffer) - 3; i++){
        if (
            buffer[i] == '\r' && buffer[i + 1] == '\n' &&
            buffer[i + 2] == '\r' && buffer[i + 3] == '\n'
        ) return 0;
    }

    return -1;
}