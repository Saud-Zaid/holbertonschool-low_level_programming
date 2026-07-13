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
			/* ننفذ العمليات فقط إذا كان الخيار صحيحاً بين 1 و 4 */
			switch (choice)
			{
			case 1:
				printf("A: ");
				scanf("%d", &a);
				printf("B: ");
				scanf("%d", &b);
				
				result = add(a, b);
				printf("Result: %d\n", result);
				break;
			
			default:
				break;
			}
		}
		
	} while (choice != 0);

	return (0);
}