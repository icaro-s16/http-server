#ifndef HTTP_RES_DISPATCHER_H
#define HTTP_RES_DISPATCHER_H

#include "http_packet.h"
#include "structures/hash_map.h"
#include "http_request_types.h"
#include "structures/d_string.h"
#include <string.h>
#include <stdlib.h>

struct String* http_dispatch_request(struct HashMap* command_map, struct Packet* packet, struct Request* request);

#endif