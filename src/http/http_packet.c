#include "http/http_packet.h"

struct Packet* http_packet_create(unsigned char* header, unsigned char* body, size_t header_size, size_t body_size){
    struct Packet* packet = malloc(sizeof(struct Packet));
    
    packet->body = NULL;
    packet->header = NULL;
    
    if (header != NULL && header_size != 0){
        packet->header = calloc(header_size, sizeof(unsigned char));
        packet->header_size = header_size;
        memcpy(packet->header, header, header_size);
    }
    if(body != NULL && body_size != 0){
        packet->body = calloc(body_size, sizeof(unsigned char));
        packet->body_size = body_size;
        memcpy(packet->body, body, body_size);
    }

    return packet;
}

/*
free the packet content and then the packet
*/
void http_packet_destroy(struct Packet* packet){
    if (packet == NULL) return; 
    if (packet->body != NULL) free(packet->body);
    if (packet->header != NULL) free(packet->header);
    free(packet);
}

/*
Return a fragmented packet into header and body
the buffer is destroyed
*/
struct Packet* http_packet_split(struct Bytes* bytes){
    unsigned char* buffer = calloc(bytes->size, sizeof(unsigned char));
    memcpy(buffer, bytes->bytes, bytes->size);


    unsigned char* header = NULL;
    unsigned char* body = NULL;

    size_t header_size = 0;
    size_t body_size = 0;
    for(int i = 0; i < bytes->size - 3; i++){
        if (
            buffer[i] == '\r' && buffer[i + 1] == '\n' &&
            buffer[i + 2] == '\r' && buffer[i + 3] == '\n'
        ){
            // Use i + 4 to lead with index zero 
            // i + 4 == sizeof(header) + 1 to include '\0' 
            header = calloc( i + 4 , sizeof(unsigned char));
            memcpy(header, buffer, i + 4);
            header_size = i + 4;

            if(bytes->size != i + 4){
                body_size = bytes->size - (i + 4);
                body = calloc(body_size + 1, sizeof(unsigned char));
                memcpy(body, &buffer[i + 4], body_size);
            }

            struct Packet* packet = http_packet_create(header, body, header_size, body_size);

            if(header != NULL) free(header);
            if(body != NULL) free(body);
            if(buffer != NULL) free(buffer);
            
            return packet;
        }
    }
    free(buffer);
    return NULL;
}