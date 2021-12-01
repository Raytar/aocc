#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

enum input_type
{
	INPUT_STRING,
	INPUT_FILE
};

typedef struct input_t
{
	enum input_type type;
	union
	{
		FILE *fp;
		const char *str;
	};
} input_t;

input_t input_new_from_str(const char *str);

input_t input_new_from_file(FILE *fp);

ssize_t input_getline(char **lineptr, size_t *n, input_t *input);

#endif // INPUT_H
