#ifndef D_STRING_H
#define D_STRING_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Bytes{
    size_t size;
    size_t capacity;
    unsigned char* bytes;
};

struct Bytes* bt_create_empty();

struct Bytes* bt_create(const unsigned char* bytes, size_t size);

struct Bytes* bt_concat(const struct Bytes* src_1, const struct Bytes* src_2);

void bt_append(struct Bytes* destination, const unsigned char* src, size_t src_size);

void bt_prepend(struct Bytes* destination, const unsigned char* src, size_t src_size);

void bt_append_byte(struct Bytes* destination, const unsigned char src);

void bt_destroy(struct Bytes* bytes);

#endif