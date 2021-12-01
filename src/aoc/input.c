#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "input.h"

static ssize_t str_getline(char **lineptr, size_t *n, const char **str)
{
	if (*str == NULL)
	{
		return -1;
	}

	const char *cur_line = *str;
	const char *next_line = strchr(cur_line, '\n'); // returns pointer to '\n', or NULL.
	next_line = next_line ? next_line + 1 : NULL;	// but we want the pointer to the next line following the terminator
	size_t len = next_line ? (next_line - cur_line) : strlen(cur_line);
	if (*n < len + 1)
	{
		if (*lineptr == NULL)
			*lineptr = malloc(len + 1);
		else
			*lineptr = realloc(*lineptr, len + 1);
		*n = len + 1;
	}
	memcpy(*lineptr, cur_line, len);
	(*lineptr)[len] = '\0';
	*str = next_line;
	return len;
}

input_t input_new_from_str(const char *str)
{
	input_t i = {
		.type = INPUT_STRING,
		.str = str,
	};
	return i;
}

input_t input_new_from_file(FILE *fp)
{
	input_t i = {
		.type = INPUT_FILE,
		.fp = fp,
	};
	return i;
}

ssize_t input_getline(char **lineptr, size_t *n, input_t *input)
{
	switch (input->type)
	{
	case INPUT_FILE:
		return getline(lineptr, n, input->fp);
	case INPUT_STRING:
		return str_getline(lineptr, n, &input->str);
	default:
		panic("invalid input type");
	}
}
