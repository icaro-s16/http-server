#include "http/http_res_builder.h"

struct String* http_build_get_header(FILE* file, struct FileStats* file_stats){
    
    char* statusCode = http_get_status_string(file);
    char* serverName = "ikrServer/1.0";
    char* date = time_get_http_format();
    size_t file_size = fs_get_file_size(file);


    char* buffer = calloc(CHUNCK_SIZE, sizeof(char));
    size_t buffer_size = CHUNCK_SIZE;

    while(1){
        
        int sn_return = snprintf(
            buffer,
            buffer_size,
            "%s\r\nDate: %s\r\nServer: %s\r\nContent-Type: %s; charset=UTF-8\r\nContent-Length: %lld\r\nConnection: keep-alive\r\n\r\n",
            statusCode,
            date,
            serverName,
            file_stats->file_type,
            file_size
        );

        if(sn_return < buffer_size) break;
            
        buffer_size = sn_return + 1 ;
        char* realloc_pointer = realloc(buffer, buffer_size);
        
        if (realloc_pointer != buffer){
            buffer = realloc_pointer;
        }

        memset(buffer, 0, buffer_size);
    
    }

    struct String* st_buffer = dstr_create(buffer);
    free(buffer);

    return st_buffer;
}

char* http_get_status_string(FILE* file){
    char* statusCode = NULL;

    if(file != NULL){
        char* status200 = "HTTP/1.1 200 OK";
        statusCode = calloc(strlen(status200) + 1, sizeof(char));
        strcpy(statusCode, status200);

    }else{
        char* status404 = "HTTP/1.1 404 Not Found";
        statusCode = calloc(strlen(status404) + 1, sizeof(char));
        strcpy(statusCode, status404);

    }

    return statusCode;
}

struct String* http_handle_get_method(struct Request* request){
    FILE* file = fs_open_public_file(request->url);
    
    struct FileStats* file_stats = fs_stat_create(request->url);
    



    struct String* response = http_build_get_header(file, file_stats);

    if (file != NULL){
        char* content = fs_read_all_content(file);
        dstr_append(response, content);
        if (content != NULL) free(content);
        if (content != NULL) fclose(file);
    }
    return response;
}