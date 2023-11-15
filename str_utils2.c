#include "main.h"

/**
 * _strdup - duplicates a str
 * @s: str
 * Return: duplicate str
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}

/**
 * _strlen - len of a string.
 * @s: pointer
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_chars - compare chars str
 * @str: string.
 * @delim: delimiter.
 *
 * Return: 1
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int z, m, a;

	for (z = 0, a = 0; str[z]; z++)
	{
		for (m = 0; delim[m]; m++)
		{
			if (str[z] == delim[m])
			{
				a++;
				break;
			}
		}
	}
	if (z == a)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string
 * @str: string.
 * @delim: delimiter.
 * Return: string
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int z, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str;
		z = _strlen(str);
		str_end = &str[z];
	}
	str_start = splitted;
	if (str_start == str_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (z = 0; delim[z]; z++)
		{
			if (*splitted == delim[z])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - string passed is a number
 * @s: string
 * Return: 1
 */
int _isdigit(const char *s)
{
	unsigned int z;

	for (z = 0; s[z]; z++)
	{
		if (s[z] < 48 || s[z] > 57)
			return (0);
	}
	return (1);
}
