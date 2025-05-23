// https://wiki.osdev.org/Meaty_Skeleton
// Modified for use with kobold

#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);

#ifdef __cplusplus
}
#endif

#endif