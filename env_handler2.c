#include "main.h"

/**
 * copy_info - create info to copy
 * @name: name
 * @value: value
 * Return: new environ or alias.
 */
char *copy_info(char *name, char *value)
{
	char *_new;
	int l_name, l_value, l;

	l_name = _strlen(name);
	l_value = _strlen(value);
	l = l_name + l_value + 2;
	_new = malloc(sizeof(char) * (l));
	_strcpy(_new, name);
	_strcat(_new, "=");
	_strcat(_new, value);
	_strcat(_new, "\0");

	return (_new);
}

/**
 * set_env - sets environment var
 * @name: name
 * @value: value
 * @datash: data struct
 * Return: none
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int z;
	char *v_env, *n_env;

	for (z = 0; datash->_environ[z]; z++)
	{
		v_env = _strdup(datash->_environ[z]);
		n_env = _strtok(v_env, "=");
		if (_strcmp(n_env, name) == 0)
		{
			free(datash->_environ[z]);
			datash->_environ[z] = copy_info(n_env, value);
			free(v_env);
			return;
		}
		free(v_env);
	}

	datash->_environ = _reallocdp(datash->_environ, z, sizeof(char *) * (z + 2));
	datash->_environ[z] = copy_info(name, value);
	datash->_environ[z + 1] = NULL;
}

/**
 * _setenv - compares environment var names
 * @datash: relevant data
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - deletes environment var
 * @datash: relevant data
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *v_env, *n_env;
	int z, m, a;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	a = -1;
	for (z = 0; datash->_environ[z]; z++)
	{
		v_env = _strdup(datash->_environ[z]);
		n_env = _strtok(v_env, "=");
		if (_strcmp(n_env, datash->args[1]) == 0)
		{
			a = z;
		}
		free(v_env);
	}
	if (a == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (z));
	for (z = m = 0; datash->_environ[z]; z++)
	{
		if (z != a)
		{
			realloc_environ[m] = datash->_environ[z];
			m++;
		}
	}
	realloc_environ[m] = NULL;
	free(datash->_environ[a]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
