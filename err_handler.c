#include "main.h"

/**
 * strcat_cd - function that concatenates msg
 * @datash: relevant data
 * @msg: message
 * @error: erroe
 * @ver_str: count line
 * Return: error mssge
 */
char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *i_f;

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		i_f = malloc(3);
		i_f[0] = '-';
		i_f[1] = datash->args[1][1];
		i_f[2] = '\0';
		_strcat(error, i_f);
		free(i_f);
	}
	else
	{
		_strcat(error, datash->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - error message
 * @datash: relevant data
 * Return: Error mssge
 */
char *error_get_cd(data_shell *datash)
{
	int len, len_id;
	char *err, *co_str, *msg;

	co_str = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	len = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	len += _strlen(co_str) + _strlen(msg) + len_id + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(co_str);
		return (NULL);
	}

	err = strcat_cd(datash, msg, err, co_str);

	free(co_str);

	return (err);
}

/**
 * error_not_found - command not found
 * @datash: relevant data
 * Return: Error mssge
 */
char *error_not_found(data_shell *datash)
{
	int len;
	char *err;
	char *co_str;

	co_str = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(co_str);
	len += _strlen(datash->args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(co_str);
		return (NULL);
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, co_str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(co_str);
	return (err);
}

/**
 * error_exit_shell - exit msg in get_exit
 * @datash: relevant data
 *
 * Return: Error mssg
 */
char *error_exit_shell(data_shell *datash)
{
	int len;
	char *err;
	char *co_str;

	co_str = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(co_str);
	len += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(co_str);
		return (NULL);
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, co_str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, datash->args[1]);
	_strcat(err, "\n\0");
	free(co_str);

	return (err);
}
