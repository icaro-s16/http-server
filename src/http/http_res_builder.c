#include "http/http_res_builder.h"

struct Bytes* http_build_get_header(FILE* file, struct FileStats* file_stats){
    
    char* status_code = http_get_status(file);
    char* serverName = "ikrServer/1.0";
    char* date = time_get_http_format();
    size_t file_size = fs_get_file_size(file);


    char* buffer = calloc(CHUNCK_SIZE, sizeof(char));
    size_t buffer_size = CHUNCK_SIZE;

    while(1){
        
        int sn_return = snprintf(
            buffer,
            buffer_size,
            "%s\r\nDate: %s\r\nServer: %s\r\nContent-Type: %s\r\nContent-Length: %lld\r\nConnection: close\r\n\r\n",
            status_code,
            date,
            serverName,
            file_stats->file_type,
            file_size
        );

        
        if(sn_return < buffer_size){
            buffer_size = sn_return; 
            break;
        };
        
        
        buffer_size = sn_return + 1;
        char* aux = realloc(buffer, buffer_size);
        buffer = (aux != buffer) ? aux : buffer;
        memset(buffer, 0, buffer_size);
    
    }

    struct Bytes* bytes = bt_create(buffer, buffer_size);
    if (buffer != NULL )free(buffer);
    if (date != NULL) free(date);
    if (status_code != NULL) free(status_code);

    return bytes;
}

char* http_get_status(FILE* file){
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

struct Bytes* http_handle_get_method(struct Request* request, struct HashMap* mime_map){
    FILE* file = fs_open_public_file(request->url);
    
    struct FileStats* file_stats = fs_stat_create(request->url, mime_map);

    struct Bytes* response = http_build_get_header(file, file_stats);

    if (file != NULL){
        unsigned char* content = fs_read_all_content(file);
        size_t content_size = fs_get_file_size(file); 
        bt_append(response, content, content_size);
        if (content != NULL) free(content);
        fclose(file);
    }

    if (file_stats != NULL) fs_stat_destroy(file_stats);
    return response;
}