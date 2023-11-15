#include "main.h"

/**
 * is_cdir - check if ":" is in the current directory.
 * @path: path
 * @i: pointer of index.
 * Return: 1 if the path exists in the cd, 0 otherwise.
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - locates command
 *
 * @cmd: command
 * @_environ: envir variable
 * Return: location of command.
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *pointer_pa_th, *token_pa_th, *d;
	int len_d, len_c, z;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		pointer_pa_th = _strdup(path);
		len_c = _strlen(cmd);
		token_pa_th = _strtok(pointer_pa_th, ":");
		z = 0;
		while (token_pa_th != NULL)
		{
			if (is_cdir(path, &z))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_d = _strlen(token_pa_th);
			d = malloc(len_d + len_c + 2);
			_strcpy(d, token_pa_th);
			_strcat(d, "/");
			_strcat(d, cmd);
			_strcat(d, "\0");
			if (stat(d, &st) == 0)
			{
				free(pointer_pa_th);
				return (d);
			}
			free(d);
			token_pa_th = _strtok(NULL, ":");
		}
		free(pointer_pa_th);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if executable
 *
 * @datash: data struct
 * Return: 0 if is not executable, other number if it does
 */
int is_executable(data_shell *datash)
{
	struct stat st;
	int z;
	char *in_put;

	in_put = datash->args[0];
	for (z = 0; in_put[z]; z++)
	{
		if (in_put[z] == '.')
		{
			if (in_put[z + 1] == '.')
				return (0);
			if (in_put[z + 1] == '/')
				continue;
			else
				break;
		}
		else if (in_put[z] == '/' && z != 0)
		{
			if (in_put[z + 1] == '.')
				continue;
			z++;
			break;
		}
		else
			break;
	}
	if (z == 0)
		return (0);

	if (stat(in_put + z, &st) == 0)
	{
		return (z);
	}
	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - confirms if user has permissions to access
 *
 * @dir: destination dir
 * @datash: data struct
 * Return: 1 if there is an error, 0 if none
 */
int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - execute command lines
 *
 * @datash: data relevant
 * Return: 1 on success.
 */
int cmd_exec(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int sta_te;
	int exc;
	char *d;
	(void) wpd;

	exc = is_executable(datash);
	if (exc == -1)
		return (1);
	if (exc == 0)
	{
		d = _which(datash->args[0], datash->_environ);
		if (check_error_cmd(d, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exc == 0)
			d = _which(datash->args[0], datash->_environ);
		else
			d = datash->args[0];
		execve(d + exc, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &sta_te, WUNTRACED);
		} while (!WIFEXITED(sta_te) && !WIFSIGNALED(sta_te));
	}

	datash->status = sta_te / 256;
	return (1);
}
