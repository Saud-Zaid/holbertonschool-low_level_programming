#include "main.h"

/**
 * _strncat - concatenates two strings using at most n bytes
 * @dest: destination string
 * @src: source string
 * @n: maximum number of bytes to use from src
 *
 * Return: pointer to dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0;
	int j = 0;

	/* الوصول لنهاية النص الأول */
	while (dest[i] != '\0')
	{
		i++;
	}

	/* نسخ النص الثاني بشرط عدم تجاوز نهاية النص أو العدد n */
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';

	return (dest);
}
