#include "main.h"

/**
 * cmp_env_name - compares environment var names
 * @nenv: name of environment variable
 * @name: passed name
 *
 * Return: 0
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int z;

	for (z = 0; nenv[z] != '='; z++)
	{
		if (nenv[z] != name[z])
		{
			return (0);
		}
	}

	return (z + 1);
}

/**
 * _getenv - get environment variable
 * @name: name
 * @_environ: environment var
 *
 * Return: value of environ var
 */
char *_getenv(const char *name, char **_environ)
{
	char *pointer_env;
	int z, mo_ve;

	pointer_env = NULL;
	mo_ve = 0;

	for (z = 0; _environ[z]; z++)
	{
		mo_ve = cmp_env_name(_environ[z], name);
		if (mo_ve)
		{
			pointer_env = _environ[z];
			break;
		}
	}

	return (pointer_env + mo_ve);
}

/**
 * _env - prints evironment var
 *
 * @datash: relevant data
 * Return: 1 on success
 */
int _env(data_shell *datash)
{
	int z, m;

	for (z = 0; datash->_environ[z]; z++)
	{

		for (m = 0; datash->_environ[z][m]; m++)
			;

		write(STDOUT_FILENO, datash->_environ[z], m);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
