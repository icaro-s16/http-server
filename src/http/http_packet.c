#include "http/http_packet.h"

struct Packet* http_packet_create(char* header, char* body){
    struct Packet* packet = malloc(sizeof(struct Packet));
    packet->body = NULL;
    packet->header = NULL;
    if (header != NULL && strlen(header) != 0){
        packet->header = calloc(strlen(header) + 1, sizeof(char));
        strcpy(packet->header, header);
    }
    if(body != NULL && strlen(body) != 0){
        packet->body = calloc(strlen(body) + 1, sizeof(char));
        strcpy(packet->body, body);
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
struct Packet* http_packet_split(struct String* string){
    char* buffer = calloc(string->size + 1, sizeof(char));
    strcpy(buffer, string->c_str);


    char* header = NULL;
    char* body = NULL;
    for(int i = 0; i < strlen(buffer) - 3; i++){
        if (
            buffer[i] == '\r' && buffer[i + 1] == '\n' &&
            buffer[i + 2] == '\r' && buffer[i + 3] == '\n'
        ){
            // Use i + 4 to lead with index zero 
            // i + 4 == sizeof(header) + 1 to include '\0' 
            header = calloc( i + 5 , sizeof(char));
            memcpy(header, buffer, i + 4);

            if(strlen(buffer) != i + 4){
                size_t body_size = strlen(buffer) - (i + 4);
                body = calloc(body_size + 1, sizeof(char));
                memcpy(body, &buffer[i + 4], body_size);
            }

            struct Packet* packet = http_packet_create(header, body);

            if(header != NULL) free(header);
            if(body != NULL) free(body);
            
            return packet;
        }
    }
    free(buffer);
    return NULL;
}