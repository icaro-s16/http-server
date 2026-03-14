#include "structures/d_string.h"

struct String* dstr_create_empty(){
    struct String* string = malloc(sizeof(struct String));
    string->size = 0;
    string->capacity = 25;
    string->c_str = calloc(string->capacity, sizeof(char));
    return string;
}

struct String* dstr_create(const char* st){
    struct String* string = malloc(sizeof(struct String));
    string->size = strlen(st);
    string->capacity = 25;
    while(string->capacity < strlen(st)){
        string->capacity *= 2;
    }
    string->c_str = calloc(string->capacity, sizeof(char));
    memcpy(string->c_str, st, strlen(st));
    return string;
}

struct String* dstr_concat(const struct String* string1, const struct String* string2){
    struct String* string = dstr_create_empty();
    
    size_t total_size = string1->size + string2->size;
    
    string->size = total_size;
    int realloc_fl = -1;
    while(string->capacity < total_size){
        string->capacity *= 2;
        realloc_fl = 0;
    }

    if(realloc_fl == 0){
        char* aux_pointer = realloc(string->c_str, string->capacity);
        if(aux_pointer != string->c_str){
            string->c_str = aux_pointer;
        }
        memset(&string->c_str[string->size], 0, string->capacity - string->size);
    }

    memcpy(string->c_str, string1->c_str, string1->size);
    memcpy(&string->c_str[string1->size], string2->c_str, string2->size);

    return string;
}

void dstr_append(struct String* string, const char* c_st){
    if (c_st == NULL || strlen(c_st) == 0 || string == NULL) return;
    
    size_t total_size = string->size + strlen(c_st) + 1;
    size_t size_before = (string->c_str == NULL) ? 0 : strlen(string->c_str);

    string->size = total_size;

    int realloc_fl = -1;
    while(string->capacity < total_size){
        string->capacity *= 2;
        realloc_fl = 0;
    }

    if (realloc_fl == 0){
        char* aux_pointer = realloc(string->c_str, string->capacity);

        string->c_str = (aux_pointer != string->c_str) ? aux_pointer : string->c_str;

        memset(&string->c_str[size_before], 0, string->capacity - size_before);
    
    }

    memcpy(&string->c_str[size_before], c_st, strlen(c_st));
}

void dstr_prepend(const char* c_st, struct String* string){
    string->size = strlen(c_st) + string->size;

    size_t size_before = strlen(c_st);

    char* sub_string = calloc(string->size + 1, sizeof(char));
    strcpy(sub_string, string->c_str);

    int realloc_fl = -1;
    while (string->capacity < string->size){
        string->capacity *= 2;
        realloc_fl = 0;
    }

    if(realloc_fl == 0){
        char* aux_pointer = realloc(string->c_str, string->capacity);
        
        string->c_str = (aux_pointer != string->c_str) ? aux_pointer : string->c_str;

        memset(string->c_str, 0,  string->capacity);
    }
    
    memcpy(string->c_str, c_st, size_before);
    memcpy(&string->c_str[size_before], sub_string, strlen(sub_string));

    if (sub_string != NULL) free(sub_string);
}

void dstr_append_char(struct String* string, const char ch){
    
    string->size ++;
    size_t size_before = strlen(string->c_str);

    int realloc_fl = -1;
    
    if(string->size >= string->capacity){
        string->capacity *= 2;
        realloc_fl = 0;
    }

    if(realloc_fl == 0){
        char* auxPointer = realloc(string->c_str, string->capacity);
        if (auxPointer != string->c_str){
            string->c_str = auxPointer;
        }
        memset(&string->c_str[size_before], 0, string->capacity - string->size);
    }

    memcpy(&string->c_str[size_before], &ch, 1);
}

void dstr_destroy(struct String* string){
    if(string == NULL) return;

    if(string->c_str != NULL) free(string->c_str);
    
    free(string);
}