#include "main.h"

/**
 * _atoi - converts a string to an integer
 * @s: string to convert
 *
 * Return: the converted integer
 */
int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	int res = 0;
	int found_num = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			found_num = 1;
			/* بناء الرقم بالاتجاه السالب لتفادي الطفح */
			if (sign == 1)
			{
				res = (res * 10) - (s[i] - '0');
			}
			else
			{
				res = (res * 10) + (s[i] - '0');
			}
		}
		else if (found_num)
		{
			break;
		}
		i++;
	}

	if (sign == 1)
	{
		return (-res);
	}
	return (res);
}
