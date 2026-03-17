#include "http/http_router.h"

struct HashMap* http_init_req_router(){
    struct HashMap* http_map = hashmap_create("Request", &http_parse_request_line, sizeof(void(*)(char*, struct Request*)));
    hashmap_insert(http_map, "Connection", &http_parse_connection_header);
    
    return http_map;
    
};

struct HashMap* http_init_res_router(){
    struct HashMap* http_map = hashmap_create("GET", &http_handle_get_method, sizeof(struct Bytes* (*) (struct Request*, struct HashMap*)));
    return http_map;
}


struct HashMap* http_init_mime_router(){
    struct HashMap* http_mime_map = hashmap_create("html", &create_text_mime, sizeof(create_text_mime));
    hashmap_insert(http_mime_map, "css", &create_text_mime);
    hashmap_insert(http_mime_map, "jpeg",&create_image_mime);
    hashmap_insert(http_mime_map, "png",&create_image_mime);
    hashmap_insert(http_mime_map, "jpg",&create_image_mime);
    hashmap_insert(http_mime_map, "mp3",&create_video_mime);
    hashmap_insert(http_mime_map, "mp4",&create_video_mime);
    hashmap_insert(http_mime_map, "gif", &create_video_mime);
    return http_mime_map;
}