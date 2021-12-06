#include <stdio.h>	// sscanf
#include <stdlib.h> // free
#include <string.h> // strchr

#include "solutions.h"

void parse_line(char *line, char **command_ptr, unsigned *value_ptr)
{
	*command_ptr = line;
	char *value_str = strchr(line, ' ');
	if (!value_str)
		panicf("expected line to be formatted as \"[command] [value]\", but got \"%s\"", line);

	*value_str = '\0'; // null terminates command
	value_str++;

	if (sscanf(value_str, "%u", value_ptr) != 1)
		panic("could not read value");
}

int64_t day2_part1(FILE *input)
{
	int64_t horizontal_pos = 0;
	int64_t depth = 0;

	char *line = NULL;
	size_t buf_len = 0;

	while (getline(&line, &buf_len, input) != -1)
	{
		char *command;
		unsigned value;

		parse_line(line, &command, &value);

		if (strcmp("forward", command) == 0)
			horizontal_pos += value;
		else if (strcmp("down", command) == 0)
			depth += value;
		else if (strcmp("up", command) == 0)
			depth -= value;
		else
			panicf("unknown command '%s'", command);
	}

	if (line != NULL)
		free(line);

	return horizontal_pos * depth;
}

int64_t day2_part2(FILE *input)
{
	int64_t horizontal_pos = 0;
	int64_t depth = 0;
	int64_t aim = 0;

	char *line = NULL;
	size_t buf_len = 0;

	while (getline(&line, &buf_len, input) != -1)
	{
		char *command;
		unsigned value;

		parse_line(line, &command, &value);

		if (strcmp("forward", command) == 0)
		{
			horizontal_pos += value;
			depth += aim * value;
		}
		else if (strcmp("down", command) == 0)
			aim += value;
		else if (strcmp("up", command) == 0)
			aim -= value;
		else
			panicf("unknown command '%s'", command);
	}

	if (line != NULL)
		free(line);

	return horizontal_pos * depth;
}
