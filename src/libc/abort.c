// https://wiki.osdev.org/Meaty_Skeleton
// Modified for use with kobold

#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void) {
    printf("KERNEL PANIC");
	__builtin_unreachable();
}