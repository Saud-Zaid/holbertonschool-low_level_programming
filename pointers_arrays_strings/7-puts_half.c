#include "main.h"

/**
 * puts_half - prints the second half of a string
 * @str: string to split and print
 *
 * Return: void
 */
void puts_half(char *str)
{
	int length = 0;
	int start;

	/* حساب الطول الإجمالي للنص */
	while (str[length] != '\0')
	{
		length++;
	}

	/* تحديد نقطة البداية بناءً على كون الطول زوجياً أو فردياً */
	if (length % 2 == 0)
	{
		start = length / 2;
	}
	else
	{
		start = (length + 1) / 2;
	}

	/* طباعة النصف الثاني */
	while (str[start] != '\0')
	{
		_putchar(str[start]);
		start++;
	}
	_putchar('\n');
}
