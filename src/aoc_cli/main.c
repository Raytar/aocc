#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

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

	struct timeval tval_before, tval_after, tval_result;
	gettimeofday(&tval_before, NULL);

	if (strcmp(argv[1], "2021") == 0)
	{
		aoc_2021_run_solution(day, part, fp);
	}

	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);

	printf("\nTime elapsed: %lds %06ldµs\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);

	fclose(fp);
	return 0;
}
