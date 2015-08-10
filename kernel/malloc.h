#ifndef _FROSTED_MALLOC_H
#define _FROSTED_MALLOC_H

#include "string.h"

void * f_malloc(size_t size);
void * f_calloc(size_t num, size_t size);
void* f_realloc(void* ptr, size_t size);
void f_free(void * ptr);

#endif /* _FROSTED_MALLOC_H */
