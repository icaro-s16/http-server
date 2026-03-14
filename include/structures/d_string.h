#ifndef D_STRING_H
#define D_STRING_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct String{
    size_t size;
    size_t capacity;
    char* c_str;
};

struct String* dstr_create_empty();

struct String* dstr_create(const char* st);

struct String* dstr_concat(const struct String* string1, const struct String* string2);

void dstr_append(struct String* string, const char* c_st);

void dstr_prepend(const char* c_st, struct String* string);

void dstr_append_char(struct String* string, const char ch);

void dstr_destroy(struct String* string);

#endif