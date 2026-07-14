#include "main.h"

/**
 * puts2 - prints every other character of a string
 * @str: string to print from
 *
 * Return: void
 */
void puts2(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i += 2;

		if (str[i - 1] == '\0')
		{
			break;
		}
	}
	_putchar('\n');
}
