#include "main.h"

/**
 * cd_shell - change current dir
 *
 * @datash: relevant data
 * Return: 1 (success)
 */
int cd_shell(data_shell *datash)
{
	char *d;
	int r, k, i;

	d = datash->args[1];

	if (d != NULL)
	{
		r = _strcmp("$HOME", d);
		k = _strcmp("~", d);
		i = _strcmp("--", d);
	}

	if (d == NULL || !r || !k || !i)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", d) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", d) == 0 || _strcmp("..", d) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
