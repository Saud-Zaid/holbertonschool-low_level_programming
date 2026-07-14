#include "main.h"

/**
 * _strcpy - copies string from src to dest
 * @dest: destination buffer
 * @src: source string to copy
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
