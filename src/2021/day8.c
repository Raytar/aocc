#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

#include "solutions.h"
#include "datastructures.h"

const int POW_10[] = {1, 10, 100, 1000};

int64_t aoc2021_8_1(FILE *input)
{
	char *line = NULL;
	size_t buf_len = 0;

	int64_t answer = 0;

	while (getline(&line, &buf_len, input) != -1)
	{
		line[strcspn(line, "\r\n")] = '\0'; // remove newline

		char *sep = strchr(line, '|');
		if (!sep)
			panic("could not find a '|' in the line");

		*sep = '\0';
		// char *signal_patterns = line;
		char *output_value = sep + 1;

		char *token = strtok(output_value, " ");
		while (token != NULL)
		{
			switch (strlen(token))
			{
			case 2: // 1
			case 3: // 7
			case 4: // 4
			case 7: // 8
				answer++;
				break;
			}
			token = strtok(NULL, " ");
		}
	}

	if (line)
		free(line);

	return answer;
}

// Returns true if pattern a contains b (b is a subset of a).
// Both patterns are assumed to be sorted.
static bool contains_pattern(const char *a, const char *b)
{
	if (!a || !b)
		return false;

	if (strlen(a) < strlen(b))
		return false;

	while (*b != '\0')
	{
		// increment a until we find a maching char or until the end of a
		while (*a != *b && *a != '\0')
			a++;

		// if we reached the end of a before finding a maching char, then b cannot be a subset of a
		if (*a == '\0')
			return false;

		b++;
	}

	return true;
}

static void solve_trivial_patterns(const char **patterns, vec_str_t *unknown_patterns)
{
	for (ssize_t i = vec_str_size(unknown_patterns) - 1; i >= 0; i--)
	{
		const char *pattern = vec_str_get(unknown_patterns, i);
		size_t len = strlen(pattern);
		switch (len)
		{
		case 2: // 1
			patterns[1] = pattern;
			vec_str_remove(unknown_patterns, i);
			break;
		case 3: // 7
			patterns[7] = pattern;
			vec_str_remove(unknown_patterns, i);
			break;
		case 4: // 4
			patterns[4] = pattern;
			vec_str_remove(unknown_patterns, i);
			break;
		case 7: // 8
			patterns[8] = pattern;
			vec_str_remove(unknown_patterns, i);
			break;
		}
	}
}

static void solve_patterns(const char **patterns, vec_str_t *unknown_patterns)
{
	solve_trivial_patterns(patterns, unknown_patterns);

	// solve the rest of the patterns
	while (vec_str_size(unknown_patterns) > 0)
	{
		for (ssize_t i = vec_str_size(unknown_patterns) - 1; i >= 0; i--)
		{
			const char *pattern = vec_str_get(unknown_patterns, i);
			size_t len = strlen(pattern);

			// we can solve it by looking at which patterns are subsets of others
			switch (len)
			{
			case 6: // 0 6 9
				if (contains_pattern(pattern, patterns[7]) && contains_pattern(pattern, patterns[4]))
				{
					// we have found 9
					patterns[9] = pattern;
					vec_str_remove(unknown_patterns, i);
				}
				else if (contains_pattern(pattern, patterns[1]))
				{
					// we have found 0
					patterns[0] = pattern;
					vec_str_remove(unknown_patterns, i);
				}
				else
				{
					// we have found 6
					patterns[6] = pattern;
					vec_str_remove(unknown_patterns, i);
				}
				break;
			case 5: // 2 3 5
				if (contains_pattern(pattern, patterns[7]))
				{
					// we have found 3
					patterns[3] = pattern;
					vec_str_remove(unknown_patterns, i);
				}
				else if (contains_pattern(patterns[9], pattern))
				{
					// we have found 5
					patterns[5] = pattern;
					vec_str_remove(unknown_patterns, i);
				}
				else if (patterns[9] != NULL) // the previous check could fail if 9 is not found yet
				{
					// we have found 2
					patterns[2] = pattern;
					vec_str_remove(unknown_patterns, i);
				}
				break;
			default:
				panicf("there should be no patterns here with length '%zu'", len);
			}
		}
	}
}

static int64_t process_entry(char *line)
{
	vec_str_t *unknown_patterns = vec_str_new_with_capacity(10);
	const char *patterns[10] = {NULL};

	line[strcspn(line, "\r\n")] = '\0'; // remove newline

	char *sep = strchr(line, '|');
	if (!sep)
		panic("could not find a '|' in the line");

	*sep = '\0';
	char *signal_patterns = line;
	char *output_value = sep + 1;

	// read and sort patterns
	char *pattern = strtok(signal_patterns, " ");
	while (pattern != NULL)
	{
		size_t len = strlen(pattern);
		// sort the pattern
		qsort(pattern, len, sizeof(char), (cmp_fn)cmp_char);
		vec_str_push_back(unknown_patterns, pattern);
		pattern = strtok(NULL, " ");
	}

	solve_patterns(patterns, unknown_patterns);

	int64_t output = 0;
	int position = 3;
	// now compute the output value
	char *digit = strtok(output_value, " ");
	while (position >= 0)
	{
		size_t len = strlen(digit);
		// sort the pattern
		qsort(digit, len, sizeof(char), (cmp_fn)cmp_char);

		for (int i = 0; i < 10; i++)
		{
			if (strcmp(digit, patterns[i]) == 0)
				output += i * POW_10[position--];
		}

		digit = strtok(NULL, " ");
	}

	vec_str_free(unknown_patterns);

	printf("output: %" PRIi64 "\n", output);

	return output;
}

int64_t aoc2021_8_2(FILE *input)
{
	char *line = NULL;
	size_t buf_len = 0;

	int64_t answer = 0;

	while (getline(&line, &buf_len, input) != -1)
		answer += process_entry(line);

	if (line)
		free(line);

	return answer;
}
