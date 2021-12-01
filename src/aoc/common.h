#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdnoreturn.h>

#include "input.h"

// function pointer type for AoC solutions
typedef int64_t (*solution_t)(input_t);

#define panic(message) aoc_panic(__FILE__, __LINE__, message)

noreturn void aoc_panic(const char *file, int line, const char *message);

#define panicf(format, ...) aoc_panicf(__FILE__, __LINE__, format, __VA_ARGS__)

noreturn void aoc_panicf(const char *file, int line, const char *format, ...);

#endif // COMMON_H
