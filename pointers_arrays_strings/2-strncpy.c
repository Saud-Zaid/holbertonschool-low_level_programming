#include "main.h"

/**
 * _strncpy - copies a string
 * @dest: destination string
 * @src: source string
 * @n: max number of bytes to copy
 *
 * Return: pointer to dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	/* نسخ الحروف من المصدر إلى الوجهة */
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}

	/* ملء المساحة المتبقية بالأصفار */
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}
