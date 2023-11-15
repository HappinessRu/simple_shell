#include "main.h"

/**
 * get_len - length of a number.
 * @n: number.
 * Return: Length of a number.
 */
int get_len(int n)
{
	unsigned int abs_v;
	int len = 1;

	if (n < 0)
	{
		len++;
		abs_v = n * -1;
	}
	else
	{
		abs_v = n;
	}
	while (abs_v > 9)
	{
		len++;
		abs_v = abs_v / 10;
	}

	return (len);
}
/**
 * aux_itoa - int to string.
 * @n: number
 * Return: String.
 */
char *aux_itoa(int n)
{
	unsigned int abs_v;
	int len = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + len) = '\0';

	if (n < 0)
	{
		abs_v = n * -1;
		buffer[0] = '-';
	}
	else
	{
		abs_v = n;
	}

	len--;
	do {
		*(buffer + len) = (abs_v % 10) + '0';
		abs_v = abs_v / 10;
		len--;
	}
	while (abs_v > 0)
		;
	return (buffer);
}

/**
 * _atoi - string to an integer.
 * @s:string.
 * Return: int
 */
int _atoi(char *s)
{
	unsigned int co_unt = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + co_unt) != '\0')
	{
		if (size > 0 && (*(s + co_unt) < '0' || *(s + co_unt) > '9'))
			break;

		if (*(s + co_unt) == '-')
			pn *= -1;

		if ((*(s + co_unt) >= '0') && (*(s + co_unt) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		co_unt++;
	}

	for (i = co_unt - size; i < co_unt; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
