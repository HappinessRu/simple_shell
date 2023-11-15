#include "main.h"

/**
 * exit_shell - exits shell
 *
 * @datash: relevant data
 * Return: 0 (success.)
 */
int exit_shell(data_shell *datash)
{
	unsigned int ustatus;
	int is_d;
	int str_len;
	int bg_num;

	if (datash->args[1] != NULL)
	{
		ustatus = _atoi(datash->args[1]);
		is_d = _isdigit(datash->args[1]);
		str_len = _strlen(datash->args[1]);
		bg_num = ustatus > (unsigned int)INT_MAX;
		if (!is_d || str_len > 10 || bg_num)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustatus % 256);
	}
	return (0);
}
