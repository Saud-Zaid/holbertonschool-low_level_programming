#include <stdio.h>

/**
 * add - Adds two integers
 * @a: First integer
 * @b: Second integer
 * Return: Sum of a and b
 */
int add(int a, int b)
{
	return (a + b);
}

/**
 * sub - Subtracts second integer from the first
 * @a: First integer
 * @b: Second integer
 * Return: Difference of a and b
 */
int sub(int a, int b)
{
	return (a - b);
}

/**
 * mul - Multiplies two integers
 * @a: First integer
 * @b: Second integer
 * Return: Product of a and b
 */
int mul(int a, int b)
{
	return (a * b);
}

/**
 * div_op - Divides first integer by the second
 * @a: First integer (numerator)
 * @b: Second integer (denominator)
 * Return: Floating point result of division
 */
double div_op(int a, int b)
{
	return ((double)a / b);
}

/**
 * main - Entry point for the simple calculator program
 * Return: Always 0 (Success)
 */
int main(void)
{
	int choice;
	int a, b, result;

	do {
		printf("Simple Calculator\n");
		printf("1) Add\n");
		printf("2) Subtract\n");
		printf("3) Multiply\n");
		printf("4) Divide\n");
		printf("0) Quit\nChoice: ");
		
		scanf("%d", &choice);
		
		if (choice == 0)
		{
			printf("Bye!\n");
		}
		else if (choice < 0 || choice > 4)
		{
			printf("Invalid choice\n");
		}
		else
		{
			printf("A: ");
			scanf("%d", &a);
			printf("B: ");
			scanf("%d", &b);

			switch (choice)
			{
			case 1:
				result = add(a, b);
				printf("Result: %d\n", result);
				break;
				
			case 2:
				result = sub(a, b);
				printf("Result: %d\n", result);
				break;

			case 3:
				result = mul(a, b);
				printf("Result: %d\n", result);
				break;

			case 4:
				if (b == 0)
				{
					printf("Error: division by zero\n");
				}
				else
				{
					/* استخدام %g أو %.1f للطباعة العشري الذكية */
					printf("Result: %g\n", div_op(a, b));
				}
				break;
			
			default:
				break;
			}
		}
		
	} while (choice != 0);

	return (0);
}