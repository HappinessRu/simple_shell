#include "main.h"

/**
 * rev_string - reverses a string.
 * @s: string.
 * Return: none
 */
void rev_string(char *s)
{
	int co_unt = 0, z, m;
	char *str, tem;

	while (co_unt >= 0)
	{
		if (s[co_unt] == '\0')
			break;
		co_unt++;
	}
	str = s;

	for (z = 0; z < (co_unt - 1); z++)
	{
		for (m = z + 1; m > 0; m--)
		{
			tem = *(str + m);
			*(str + m) = *(str + (m - 1));
			*(str + (m - 1)) = tem;
		}
	}
}
