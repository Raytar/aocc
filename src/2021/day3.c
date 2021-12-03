#include <stdlib.h> // free
#include <string.h> // strcspn
#include <stdbool.h>
#include <aoc/vec.h>
#include "solutions.h"

struct bit
{
	int zeros;
	int ones;
};

VEC_DECLARE_TYPE_NAME(struct bit, bit)
VEC_IMPL_TYPE_NAME(struct bit, bit)

VEC_DECLARE_TYPE(short)
VEC_IMPL_TYPE(short)

vec_short_t *read_input(input_t input, size_t *num_bits)
{
	char *line = NULL;
	size_t buf_len = 0;

	vec_short_t *numbers = vec_short_new();

	while (input_getline(&line, &buf_len, &input) != -1)
	{
		size_t len;

		line[strcspn(line, "\r\n")] = '\0'; // trim newline

		if ((len = strlen(line)) > *num_bits)
			*num_bits = len;

		short number = 0;
		for (size_t i = 0; i < len; i++)
		{
			int bit_number = len - i - 1;
			switch (line[i])
			{
			case '1':
				number |= (1 << bit_number);
				break;
			case '0':
				break;
			default:
				panicf("unexpected character in input: '%c'", line[i]);
			}
		}
		vec_short_push_back(numbers, number);
	}

	if (line != NULL)
		free(line);

	return numbers;
}

vec_bit_t *count_bits(vec_short_t *numbers, size_t num_bits)
{
	vec_bit_t *bits = vec_bit_new_with_capacity(num_bits);
	vec_bit_set_size(bits, num_bits);

	for (size_t i = 0; i < vec_short_size(numbers); i++)
	{
		short number = vec_short_get(numbers, i);
		for (size_t j = 0; j < num_bits; j++)
		{
			int bit_number = num_bits - j - 1;
			struct bit *bit_ptr = vec_bit_get_ptr(bits, j);
			if (number & (1 << bit_number))
				bit_ptr->ones++;
			else
				bit_ptr->zeros++;
		}
	}

	return bits;
}

int64_t day3_part1(input_t input)
{
	size_t num_bits = 0;
	vec_short_t *numbers = read_input(input, &num_bits);
	vec_bit_t *bits = count_bits(numbers, num_bits);

	int64_t gamma_rate = 0;
	int64_t epsilon_rate = 0;

	for (size_t i = 0; i < num_bits; i++)
	{
		struct bit bit = vec_bit_get(bits, i);
		if (bit.ones > bit.zeros)
			gamma_rate |= 1 << (num_bits - i - 1);
		else
			epsilon_rate |= 1 << (num_bits - i - 1);
	}

	vec_short_free(numbers);
	vec_bit_free(bits);

	return gamma_rate * epsilon_rate;
}

void filter_numbers(vec_short_t *numbers, int bit, bool value)
{
	if (vec_short_size(numbers) == 1)
		return;

	for (int i = vec_short_size(numbers) - 1; i >= 0; i--)
	{
		short number = vec_short_get(numbers, i);
		if (!!(number & (1 << bit)) != value)
			vec_short_remove(numbers, i);
	}
}

int64_t day3_part2(input_t input)
{
	size_t num_bits = 0;
	vec_short_t *oxygen_numbers = read_input(input, &num_bits);
	vec_short_t *co2_numbers = vec_short_clone(oxygen_numbers);
	vec_bit_t *oxygen_bits = count_bits(oxygen_numbers, num_bits);
	vec_bit_t *co2_bits = vec_bit_clone(oxygen_bits);

	for (size_t i = 0; i < num_bits; i++)
	{
		int bit_number = num_bits - i - 1;

		struct bit oxygen_bit = vec_bit_get(oxygen_bits, i);
		if (oxygen_bit.ones > oxygen_bit.zeros)
			filter_numbers(oxygen_numbers, bit_number, 1);
		else if (oxygen_bit.ones < oxygen_bit.zeros)
			filter_numbers(oxygen_numbers, bit_number, 0);
		else
			filter_numbers(oxygen_numbers, bit_number, 1);

		vec_bit_free(oxygen_bits);
		oxygen_bits = count_bits(oxygen_numbers, num_bits);

		struct bit co2_bit = vec_bit_get(co2_bits, i);
		if (co2_bit.ones > co2_bit.zeros)
			filter_numbers(co2_numbers, bit_number, 0);
		else if (co2_bit.ones < co2_bit.zeros)
			filter_numbers(co2_numbers, bit_number, 1);
		else
			filter_numbers(co2_numbers, bit_number, 0);

		vec_bit_free(co2_bits);
		co2_bits = count_bits(co2_numbers, num_bits);
	}

	if (vec_short_size(oxygen_numbers) != 1 || vec_short_size(co2_numbers) != 1)
	{
		panic("expected one number to remain");
	}

	int64_t oxygen_rating = vec_short_pop_back(oxygen_numbers);
	int64_t co2_rating = vec_short_pop_back(co2_numbers);

	vec_bit_free(oxygen_bits);
	vec_bit_free(co2_bits);
	vec_short_free(oxygen_numbers);
	vec_short_free(co2_numbers);

	return oxygen_rating * co2_rating;
}
