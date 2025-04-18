#include <limits.h>
#include <term/term.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int itoa(int value, char *sp, int radix)
{
    char tmp[16];// be careful with the length of the buffer
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (radix == 10 && value < 0);    
    if (sign)
        v = -value;
    else
        v = (unsigned)value;

    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix;
        if (i < 10)
          *tp++ = i+'0';
        else
          *tp++ = i + 'a' - 10;
    }

    int len = tp - tmp;

    if (sign) 
    {
        *sp++ = '-';
        len++;
    }

    while (tp > tmp)
        *sp++ = *--tp;

    return len;
}

int ltoa(long int value, char *sp, int radix)
{
    char tmp[32];// be careful with the length of the buffer
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (radix == 10 && value < 0);    
    if (sign)
        v = -value;
    else
        v = (unsigned long)value;

    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix;
        if (i < 10)
          *tp++ = i+'0';
        else
          *tp++ = i + 'a' - 10;
    }

    int len = tp - tmp;

    if (sign) 
    {
        *sp++ = '-';
        len++;
    }

    while (tp > tmp)
        *sp++ = *--tp;

    return len;
}

int ultoa(unsigned long int value, char *sp, int radix)
{
    char tmp[32];// be careful with the length of the buffer
    char *tp = tmp;
    int i;
    unsigned long v;

	v = value;

    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix;
        if (i < 10)
          *tp++ = i+'0';
        else
          *tp++ = i + 'a' - 10;
    }

    int len = tp - tmp;

    while (tp > tmp)
        *sp++ = *--tp;

    return len;
}


static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (termWriteChar(bytes[i]) == EOF)
			return false;
	return true;
}

int printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;

		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else if (*format == 'd') {
			format++;
			int num = va_arg(parameters, int);
			char numbuf[20];
			int len = itoa(num, numbuf, 10);
			if (maxrem < (unsigned long)len)
				return -1;
			if (!print(numbuf, len))
				return -1;
			written += len;
		} else if (*format == 'l') {
			format++;
			if (*format == 'i') {
				format++;
				int num = va_arg(parameters, int);
				char numbuf[32];
				int len = ltoa(num, numbuf, 10);
				if (maxrem < (unsigned long)len)
					return -1;
				if (!print(numbuf, len))
					return -1;
				written += len;
			}
			else if (*format == 'u') {
				format++;
				int num = va_arg(parameters, int);
				char numbuf[32];
				int len = ultoa(num, numbuf, 10);
				if (maxrem < (unsigned long)len)
					return -1;
				if (!print(numbuf, len))
					return -1;
				written += len;
			}
			else {
				format++;
				format++;
			}
		} else if (*format == 'p') {
			format++;
			uint64_t ptr = (uint64_t) va_arg(parameters, void*);
			char ptrbuf[40];
			ptrbuf[0] = '0';
			ptrbuf[1] = 'x';
			int len = ultoa(ptr, ptrbuf + 2, 16);
			if (maxrem < (unsigned long)len)
				return -1;
			if (!print(ptrbuf, len))
				return -1;
			written += len;
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}