#ifndef COMMON_H
#define COMMON_H

#include "input.h"

// function pointer type for AoC solutions
typedef int64_t (*solution_t)(input_t);

#define panic(message) _panic(__FILE__, __LINE__, message)

void _panic(const char *file, int line, const char *message);

#define panicf(format, ...) _panicf(__FILE__, __LINE__, format, __VA_ARGS__)

void _panicf(const char *file, int line, const char *format, ...);

#endif // COMMON_H
