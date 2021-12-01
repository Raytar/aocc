#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <2021/2021.h>

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		fprintf(stderr, "Usage: %s [year] [day] [part] [path to input]\n", argv[0]);
		return 1;
	}

	int day = atoi(argv[2]);
	int part = atoi(argv[3]);
	FILE *fp = fopen(argv[4], "r");
	if (!fp)
	{
		perror(argv[0]);
		return 1;
	}

	if (strcmp(argv[1], "2021") == 0)
	{
		aoc_2021_run_solution(day, part, fp);
	}

	fclose(fp);
	return 0;
}
