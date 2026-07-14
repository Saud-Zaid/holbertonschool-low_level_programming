#include "main.h"

/**
 * rev_string - reverses a string in-place
 * @s: string to reverse
 *
 * Return: void
 */
void rev_string(char *s)
{
	int len = 0;
	int start = 0;
	int end;
	char temp;

	/* حساب طول النص */
	while (s[len] != '\0')
	{
		len++;
	}

	end = len - 1;

	/* التبديل بين البداية والنهاية */
	while (start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;

		start++;
		end--;
	}
}
