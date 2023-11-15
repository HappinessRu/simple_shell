#include "main.h"

/**
 * cd_dot - moves to the parent directory
 *
 * @datash: relevant data
 *
 * Return: none
 */
void cd_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *d, *copy_pwd, *copy_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	copy_pwd = _strdup(pwd);
	set_env("OLDPWD", copy_pwd, datash);
	d = datash->args[1];
	if (_strcmp(".", d) == 0)
	{
		set_env("PWD", copy_pwd, datash);
		free(copy_pwd);
		return;
	}
	if (_strcmp("/", copy_pwd) == 0)
	{
		free(copy_pwd);
		return;
	}
	copy_strtok_pwd = copy_pwd;
	rev_string(copy_strtok_pwd);
	copy_strtok_pwd = _strtok(copy_strtok_pwd, "/");
	if (copy_strtok_pwd != NULL)
	{
		copy_strtok_pwd = _strtok(NULL, "\0");

		if (copy_strtok_pwd != NULL)
			rev_string(copy_strtok_pwd);
	}
	if (copy_strtok_pwd != NULL)
	{
		chdir(copy_strtok_pwd);
		set_env("PWD", copy_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(copy_pwd);
}

/**
 * cd_to - changes to a directory given
 *
 * @datash: relevant data
 * Return: none
 */
void cd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *d, *copy_pwd, *copy_d;

	getcwd(pwd, sizeof(pwd));

	d = datash->args[1];
	if (chdir(d) == -1)
	{
		get_error(datash, 2);
		return;
	}

	copy_pwd = _strdup(pwd);
	set_env("OLDPWD", copy_pwd, datash);

	copy_d = _strdup(d);
	set_env("PWD", copy_d, datash);

	free(copy_pwd);
	free(copy_d);

	datash->status = 0;

	chdir(d);
}

/**
 * cd_previous - move to the previous directory
 *
 * @datash: relevant data
 * Return: none
 */
void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *pointer_pwd, *pointer_oldpwd, *copy_pwd, *copy_oldpwd;

	getcwd(pwd, sizeof(pwd));
	copy_pwd = _strdup(pwd);

	pointer_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (pointer_oldpwd == NULL)
		copy_oldpwd = copy_pwd;
	else
		copy_oldpwd = _strdup(pointer_oldpwd);

	set_env("OLDPWD", copy_pwd, datash);

	if (chdir(copy_oldpwd) == -1)
		set_env("PWD", copy_pwd, datash);
	else
		set_env("PWD", copy_oldpwd, datash);

	pointer_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, pointer_pwd, _strlen(pointer_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(copy_pwd);
	if (pointer_oldpwd)
		free(copy_oldpwd);

	datash->status = 0;

	chdir(pointer_pwd);
}

/**
 * cd_to_home - moves to home directory
 *
 * @datash: relevant data
 * Return: none
 */
void cd_to_home(data_shell *datash)
{
	char *pointer_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	pointer_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", pointer_pwd, datash);
		free(pointer_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(pointer_pwd);
		return;
	}

	set_env("OLDPWD", pointer_pwd, datash);
	set_env("PWD", home, datash);
	free(pointer_pwd);
	datash->status = 0;
}
