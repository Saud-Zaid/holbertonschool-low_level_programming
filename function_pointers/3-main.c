#include "3-calc.h"

/**
 * main - Performs simple arithmetic operations.
 * @argc: Number of arguments.
 * @argv: Array of argument strings.
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
	int num1, num2;
	char *op;
	int (*func)(int, int);

	if (argc != 4)
	{
		printf("Error\n");
		exit(98);
	}

	num1 = atoi(argv[1]);
	op = argv[2];
	num2 = atoi(argv[3]);

	func = get_op_func(op);

	if (func == NULL)
	{
		printf("Error\n");
		exit(99);
	}

	if ((*op == '/' || *op == '%') && num2 == 0)
	{
		printf("Error\n");
		exit(100);
	}

	printf("%d\n", func(num1, num2));

	return (0);
}
