// https://wiki.osdev.org/Meaty_Skeleton
// Modified for use with kobold

#ifndef _STRING_H
#define _STRING_H 1

#include <cdefs.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
size_t strlen(const char*);

#ifdef __cplusplus
}
#endif

#endif