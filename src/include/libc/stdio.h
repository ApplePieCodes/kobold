#ifndef _STDIO_H
#define _STDIO_H 1

#include <cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

extern int printf(const char* format, ...);
int putchar(int);
int puts(const char*);

#ifdef __cplusplus
}
#endif

#endif