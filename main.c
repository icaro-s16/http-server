#include "include/networking/http_server.h"
#include "include/http/http_router.h"
#include "include/http/http_req_parser.h"
#include "include/http/http_res_dispatcher.h"
#include "include/http/http_res_builder.h"
#include "include/http/http_req_handlers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int main(){
    struct sockaddr_in serverAddr;
    struct sockaddr clientAddr;
    socklen_t clienAddrSize = sizeof(clientAddr);

    int socketClient;
    int socketServer = net_server_create(&serverAddr, IPv4);


    struct HashMap* http_request_map = http_init_req_router();

    struct HashMap* http_response_map = http_init_res_router();

    socketClient = http_server_accept(socketServer);
    
    for(int i = 0; i < 2; i ++){
        struct String* buffer = http_server_read_header(socketClient);
        
        dstr_prepend("Request: ", buffer);

        struct Request* request = http_parse_request(buffer, http_request_map);

        
        struct Packet* packet = http_packet_split(buffer);
        dstr_destroy(buffer);


        struct String* response = http_dispatch_request(http_response_map, packet, request);
        
        http_server_send_response(response, socketClient);

        dstr_destroy(response);
        http_packet_destroy(packet);
        http_req_destroy(request);
    }
    

    close(socketClient);
    hashmap_destroy(http_request_map);
    hashmap_destroy(http_response_map);
    close(socketServer);
    
    return EXIT_SUCCESS;
}