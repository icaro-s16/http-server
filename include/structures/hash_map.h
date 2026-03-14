#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 50

struct Pair{
    char key[BUFFER_SIZE];
    struct Pair* next;
    void* value;
};

struct HashMap{
    struct Pair* pairs;
    size_t sizeType;
    size_t capacity;
    size_t size;
};

size_t hashmap_calc_hash(char* msg);

void hashmap_set_pair(struct Pair* pair, char* key, void* value);

struct HashMap* hashmap_create(char* key, void* value, size_t sizeType);

struct HashMap* hashmap_create_empty(size_t sizeType);

void hashmap_insert(struct HashMap* map, char* key, void* value);

struct Pair* hashmap_get(struct HashMap* map, char* key);

struct HashMap* hashmap_rehash(struct HashMap* map);

void hashmap_free_chain(struct Pair* linkedList);

void hashmap_destroy(struct HashMap* map);

#endif