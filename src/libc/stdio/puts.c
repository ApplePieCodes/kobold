// https://wiki.osdev.org/Meaty_Skeleton
// Modified for use with kobold

#include <libc/stdio.h>

int puts(const char* string) {
	return printf("%s\n", string);
}