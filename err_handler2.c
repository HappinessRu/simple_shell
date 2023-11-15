#include "main.h"

/**
 * error_env - error message for environment
 * @datash: relevant data
 * Return: err mssge.
 */
char *error_env(data_shell *datash)
{
	int len;
	char *err;
	char *co_str;
	char *msg;

	co_str = aux_itoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	len = _strlen(datash->av[0]) + _strlen(co_str);
	len += _strlen(datash->args[0]) + _strlen(msg) + 4;
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
	_strcat(err, msg);
	_strcat(err, "\0");
	free(co_str);

	return (err);
}
/**
 * error_path_126 - err mssge
 * @datash: relevant data
 * Return: err string.
 */
char *error_path_126(data_shell *datash)
{
	int len;
	char *co_str;
	char *err;

	co_str = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(co_str);
	len += _strlen(datash->args[0]) + 24;
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
	_strcat(err, ": Permission denied\n");
	_strcat(err, "\0");
	free(co_str);
	return (err);
}
