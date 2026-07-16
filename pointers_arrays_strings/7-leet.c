#include "main.h"

/**
 * leet - encodes a string into 1337
 * @s: string to encode
 *
 * Return: pointer to s
 */
char *leet(char *s)
{
	int i = 0;
	int j;
	char l[] = "aAeEoOtTlL";
	char r[] = "4433007711";

	while (s[i] != '\0')
	{
		for (j = 0; j < 10; j++)
		{
			if (s[i] == l[j])
			{
				s[i] = r[j];
			}
		}
		i++;
	}

	return (s);
}
