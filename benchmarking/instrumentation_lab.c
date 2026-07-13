#include <stdio.h>
#include <time.h>

#define DATASET_SIZE 50000
#define SEED_VALUE 42u

static int dataset[DATASET_SIZE];

static unsigned int next_value(unsigned int *state)
{
	*state = (*state * 1103515245u) + 12345u;
	return (*state);
}

static void build_dataset(void)
{
	unsigned int state;
	int i;

	state = SEED_VALUE;

	for (i = 0; i < DATASET_SIZE; i++)
		dataset[i] = (int)(next_value(&state) % 100000);
}

static void process_dataset(void)
{
	int i;
	int v;

	for (i = 0; i < DATASET_SIZE; i++)
	{
		v = dataset[i];
		v = (v * 3) + (v / 7) - (v % 11);
		if (v < 0)
			v = -v;
		dataset[i] = v;
	}
}

static unsigned long reduce_checksum(void)
{
	unsigned long sum;
	int i;

	sum = 0;
	for (i = 0; i < DATASET_SIZE; i++)
		sum = (sum * 131ul) + (unsigned long)dataset[i];

	return (sum);
}

/**
 * main - Entry point for multi-phase instrumentation lab
 * Return: Always 0 (Success)
 */
int main(void)
{
	unsigned long checksum;
	clock_t global_start, global_end;
	clock_t start, end;
	double t_total, t_build, t_process, t_reduce;

	global_start = clock();

	/* 1. Build Phase */
	start = clock();
	build_dataset();
	end = clock();
	t_build = (double)(end - start) / (double)CLOCKS_PER_SEC;

	/* 2. Process Phase */
	start = clock();
	process_dataset();
	end = clock();
	t_process = (double)(end - start) / (double)CLOCKS_PER_SEC;

	/* 3. Reduce Phase */
	start = clock();
	checksum = reduce_checksum();
	end = clock();
	t_reduce = (double)(end - start) / (double)CLOCKS_PER_SEC;

	if (checksum == 0ul)
		printf("impossible\n");

	global_end = clock();
	t_total = (double)(global_end - global_start) / (double)CLOCKS_PER_SEC;

	/* Output Contract Compliance */
	printf("TOTAL seconds: %.6f\n", t_total);
	printf("BUILD_DATA seconds: %.6f\n", t_build);
	printf("PROCESS seconds: %.6f\n", t_process);
	printf("REDUCE seconds: %.6f\n", t_reduce);

	return (0);
}
