// https://wiki.osdev.org/Meaty_Skeleton
// Modified for use with kobold

#include <string.h>

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}