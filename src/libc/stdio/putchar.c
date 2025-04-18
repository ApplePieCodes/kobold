#include <stdio.h>

#include <term/term.h>

int putchar(int ic) {
    char c = (char)ic;
    termWriteChar(c);
	return ic;
}