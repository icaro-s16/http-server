#ifndef HTTP_PACKET_H
#define HTTP_PACKET_H

#include "structures/d_string.h"
#include <string.h>
#include <stdlib.h>

struct Packet{
    char* header;
    char* body;
};

struct Packet* http_packet_create(char* header, char* body);

void http_packet_destroy(struct Packet* packet);

struct Packet* http_packet_split(struct String* buffer);

#endif