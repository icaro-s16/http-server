#ifndef HTTP_RES_BUILDER_H
#define HTTP_RES_BUILDER_H

#include "http_packet.h"
#include "structures/hash_map.h"
#include "http_request_types.h"
#include "utils/fs_utils.h"
#include "http_date.h"
#include "chunck_size.h"
#include <string.h>
#include <stdlib.h>

struct String* http_build_get_header(FILE* file, struct FileStats* file_stats);

char* http_get_status_string(FILE* file);

struct String* http_handle_get_method(struct Request* request);

#endif