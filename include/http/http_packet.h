#ifndef HTTP_PACKET_H
#define HTTP_PACKET_H

#include "structures/bytes.h"
#include <string.h>
#include <stdlib.h>

struct Packet{
    size_t header_size;
    size_t body_size;
    unsigned char* header;
    unsigned char* body;
};

struct Packet* http_packet_create(unsigned char* header, unsigned char* body, size_t header_size, size_t body_size);

void http_packet_destroy(struct Packet* packet);

struct Packet* http_packet_split(struct Bytes* buffer);

#endif