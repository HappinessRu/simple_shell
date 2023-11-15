#include "main.h"

/**
 * _strcat - concatenate strings
 * @dest: dest
 * @src: str
 * Return: dest
 */
char *_strcat(char *dest, const char *src)
{
	int z;
	int m;

	for (z = 0; dest[z] != '\0'; z++)
		;

	for (m = 0; src[m] != '\0'; m++)
	{
		dest[z] = src[m];
		z++;
	}

	dest[z] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies the string
 * @dest: dest
 * @src: str
 * Return: dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}
/**
 * _strcmp - compares two strings.
 * @s1: string
 * @s2: string
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int z;

	for (z = 0; s1[z] == s2[z] && s1[z]; z++)
		;

	if (s1[z] > s2[z])
		return (1);
	if (s1[z] < s2[z])
		return (-1);
	return (0);
}
/**
 * _strchr - locates char in a str
 * @s: string.
 * @c: char
 * Return: pointer
 */
char *_strchr(char *s, char c)
{
	unsigned int z = 0;

	for (; *(s + z) != '\0'; z++)
		if (*(s + z) == c)
			return (s + z);
	if (*(s + z) == c)
		return (s + z);
	return ('\0');
}
/**
 * _strspn - length of a prefix substr
 * @s: string
 * @accept: accepted
 * Return: accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int z, m, bool;

	for (z = 0; *(s + z) != '\0'; z++)
	{
		bool = 1;
		for (m = 0; *(accept + m) != '\0'; m++)
		{
			if (*(s + z) == *(accept + m))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (z);
}
