#include "structures/bytes.h"

struct Bytes* bt_create_empty(){
    struct Bytes* bytes = malloc(sizeof(struct Bytes));
    bytes->size = 0;
    bytes->capacity = 25;
    bytes->bytes = calloc(25, sizeof(unsigned char));
    return bytes;
}

struct Bytes* bt_create(const unsigned char* c_bytes, size_t size){
    struct Bytes* bytes = malloc(sizeof(struct Bytes));
    bytes->capacity = 25;
    bytes->size = size;
    
    while(bytes->capacity < size){
        bytes->capacity *= 2;
    }

    bytes->bytes = calloc(bytes->capacity, sizeof(unsigned char));
    memcpy(bytes->bytes, c_bytes, size);
    return bytes;
}

struct Bytes* bt_concat(const struct Bytes* src_1, const struct Bytes* src_2){
    
    if (src_1 == NULL || src_2 == NULL) return NULL;

    struct Bytes* bytes = bt_create_empty();
    
    bytes->size = src_1->size + src_2->size;
    while(bytes->capacity < bytes->size){
        bytes->capacity *= 2;
    }

    bytes->bytes = calloc(bytes->capacity, sizeof(unsigned char));

    memcpy(bytes->bytes, src_1->bytes, src_1->size);
    memcpy(&bytes->bytes[src_1->size], src_2->bytes, src_2->size);

    return bytes;
}

void bt_append(struct Bytes* destination, const unsigned char* src, size_t src_size){
    if (destination == NULL || src_size == 0 || src == NULL) return;
    
    size_t total_size = destination->size + src_size;
    
    int realloc_fl = 0;
    while(destination->capacity < total_size){
        destination->capacity *= 2;
        realloc_fl = 1;
    }

    if (1 == realloc_fl){
        unsigned char* aux = realloc(destination->bytes, destination->capacity);
        destination->bytes = (aux != destination->bytes) ? aux : destination->bytes;
        memset(&destination->bytes[destination->size], 0, destination->capacity - destination->size);
    }

    memcpy(&destination->bytes[destination->size], src, src_size);
    destination->size = total_size;
}

void bt_prepend(struct Bytes* destination, const unsigned char* src, size_t src_size){
    if (destination == NULL || src_size == 0 || src == NULL) return;
    
    size_t total_size = destination->size + src_size;

    int realloc_fl = 0;
    while(destination->capacity < total_size){
        destination->capacity *= 2;
        realloc_fl = 1;
    }

    if (1 == realloc_fl){
        unsigned char* aux = realloc(destination->bytes, destination->capacity);
        destination->bytes = (aux != destination->bytes) ? aux : destination->bytes;
        memset(&destination->bytes[destination->size], 0, destination->capacity - destination->size);
    }

    memmove(&destination->bytes[src_size], destination->bytes, destination->size);
    memcpy(destination->bytes, src, src_size);

    destination->size = total_size;


}

void bt_append_byte(struct Bytes* destination, const unsigned char src){
    if (destination == NULL) return;

    destination->size ++;

    if (destination->capacity < destination->size){
        destination->capacity *= 2;

        unsigned char* aux = realloc(destination->bytes, destination->capacity);
        destination->bytes = (aux != destination->bytes) ? aux : destination->bytes;
        
        memset(&destination->bytes[destination->size], 0, destination->capacity - destination->size);
    }

    destination->bytes[destination->size - 1] = src;
}

void bt_destroy(struct Bytes* bytes){
    if (bytes == NULL) return;
    if (bytes->bytes != NULL) free(bytes->bytes);
    free(bytes);
}