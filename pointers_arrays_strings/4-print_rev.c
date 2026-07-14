#include "main.h"

/**
 * print_rev - prints a string, in reverse, followed by a new line
 * @s: string to print
 *
 * Return: void
 */
void print_rev(char *s)
{
	int len = 0;

	/* 1. حساب طول السلسلة النصية للوصول للنهاية */
	while (s[len] != '\0')
	{
		len++;
	}

	/* 2. الطباعة العكسية من الحرف الأخير إلى الأول */
	len--; /* تراجع خطوة لتخطي الـ Null Terminator */
	while (len >= 0)
	{
		_putchar(s[len]);
		len--;
	}
	_putchar('\n');
}
