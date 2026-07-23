#include "main.h"
#include <stdlib.h>

/**
 * string_nconcat - concatenates two strings up to n bytes of s2.
 * @s1: first string
 * @s2: second string
 * @n: number of bytes from s2 to concatenate
 *
 * Return: pointer to newly allocated memory containing s1 + n bytes of s2,
 * or NULL if allocation fails.
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	char *concat;
	unsigned int len1 = 0, len2 = 0, i = 0, j = 0;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	while (s1[len1] != '\0')
		len1++;

	while (s2[len2] != '\0')
		len2++;

	if (n < len2)
		len2 = n;

	concat = malloc(sizeof(char) * (len1 + len2 + 1));
	if (concat == NULL)
		return (NULL);

	while (i < len1)
	{
		concat[i] = s1[i];
		i++;
	}

	while (j < len2)
	{
		concat[i + j] = s2[j];
		j++;
	}

	concat[i + j] = '\0';

	return (concat);
}
