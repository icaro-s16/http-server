#include "structures/hash_map.h"

size_t hashmap_calc_hash(char* msg){
    size_t hash = 0;

    for (int i = 0; i < strlen(msg); i++) {
        hash = 31 * hash + msg[i];
    }

    return hash;
}

void hashmap_set_pair(struct Pair* pair, char* key, void* value){
    memcpy(pair->key, key, sizeof(char) * BUFFER_SIZE);
    key[BUFFER_SIZE - 1] = '\0';
    pair->value = (void*)value;
    pair->next = NULL;
}

struct HashMap* hashmap_create(char* key, void* value, size_t sizeType){
    
    struct HashMap* map = malloc(sizeof(struct HashMap));

    map->pairs = (struct Pair*)calloc(sizeof(struct Pair), 20);
    map->capacity = 20;
    map->size = 1;
    map->sizeType = sizeType;

    size_t hash = hashmap_calc_hash(key) % map->capacity;

    memcpy(map->pairs[hash].key, key, sizeof(char) * BUFFER_SIZE);
    map->pairs[hash].key[BUFFER_SIZE - 1] = '\0';
    map->pairs[hash].value = (void*)value;

    return map;
}

struct HashMap* hashmap_create_empty(size_t sizeType){
    struct HashMap* map = malloc(sizeof(struct HashMap));
    map->pairs = (struct Pair*)calloc(sizeof(struct Pair), 20);
    map->size = 0;
    map->capacity = 20;
    map->sizeType = sizeType;

    return map;
}

void hashmap_insert(struct HashMap* map, char* key, void* value){
    
    map->size ++;

    struct Pair* new_pair = malloc(sizeof(struct Pair));
    memset(new_pair, 0, sizeof(struct Pair));
    memcpy(new_pair->key, key, sizeof(char) * BUFFER_SIZE);
    new_pair->key[BUFFER_SIZE - 1] = '\0';
    new_pair->value = (void*)value;

    if ((double)map->size > (double)map->capacity * 0.75){
        map = hashmap_rehash(map);
    }

    size_t hash = hashmap_calc_hash(key) % map->capacity;
    
    if (map->pairs[hash].value != NULL) map->pairs[hash].next = new_pair;
    else{
        memcpy(&map->pairs[hash], new_pair, sizeof(struct Pair));
        free(new_pair);
    }
}

struct Pair* hashmap_get(struct HashMap* map, char* key){
    size_t hash = hashmap_calc_hash(key) % map->capacity;
    
    struct Pair* r_pair = &map->pairs[hash];

    while(strcmp(r_pair->key, key) != 0){
        if (r_pair->next == NULL) return NULL;
        r_pair = r_pair->next;
    }
    
    return r_pair;
}

struct HashMap* hashmap_rehash(struct HashMap* map){
    struct HashMap* new_map = malloc(sizeof(struct HashMap));
    new_map->capacity = map->capacity * 2;
    new_map->size = 0;
    new_map->pairs = calloc(new_map->capacity, sizeof(struct Pair));
    for(size_t i = 0; i < map->size; i++){
        
        if(map->pairs[i].value != NULL && map->pairs[i].key != NULL){
            hashmap_insert(new_map, map->pairs[i].key, map->pairs[i].value);
            
            if(map->pairs[i].next != NULL){
                
                struct Pair* move_pointer = &map->pairs[i];
                while(move_pointer->next != NULL){
                    
                    hashmap_insert(new_map, move_pointer->key, move_pointer->value);
                    move_pointer = move_pointer->next;
                
                }    
                
                hashmap_insert(new_map, move_pointer->key, move_pointer->value);
            }
        }
    }
    hashmap_destroy(map);
    return new_map;
}

void hashmap_free_chain(struct Pair* linkedList){
    if(linkedList == NULL) return;
    if (linkedList->next != NULL){
        hashmap_free_chain(linkedList->next);
    }

    free(linkedList);
}

void hashmap_destroy(struct HashMap* map){
    if (map == NULL) return;


    for(int i = 0; i < map->capacity; i++){
    
        if(map->pairs[i].next != NULL) hashmap_free_chain(map->pairs[i].next);
    
    }

    free(map->pairs);
    free(map);
}