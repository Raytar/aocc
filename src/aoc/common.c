#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void _panic(const char *file, int line, const char *message)
{
	fprintf(stderr, "panic (%s:%d): %s\n", file, line, message);
	exit(EXIT_FAILURE);
}

void _panicf(const char *file, int line, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	fprintf(stderr, "panic (%s:%d): ", file);
	vfprintf(stderr, format, args);

	va_end(args);

	exit(EXIT_FAILURE);
}
