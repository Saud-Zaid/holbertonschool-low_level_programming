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
			/* بناء الرقم دائماً كقيمة سالبة لتجنب الطفح */
			res = (res * 10) - (s[i] - '0');
		}
		else if (found_num)
		{
			break;
		}
		i++;
	}

	/* إذا كانت الإشارة النهائية موجبة، نعكس القيمة السالبة */
	if (sign == 1)
	{
		return (-res);
	}

	/* إذا كانت سالبة، نعيد القيمة السالبة كما هي */
	return (res);
}
