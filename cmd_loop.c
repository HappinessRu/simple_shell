#include "main.h"

/**
 * without_comment - deletes comments
 * @in: input
 * Return: input
 */
char *without_comment(char *in)
{
	int z, u_pto;

	u_pto = 0;
	for (z = 0; in[z]; z++)
	{
		if (in[z] == '#')
		{
			if (z == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[z - 1] == ' ' || in[z - 1] == '\t' || in[z - 1] == ';')
				u_pto = z;
		}
	}

	if (u_pto != 0)
	{
		in = _realloc(in, z, u_pto + 1);
		in[u_pto] = '\0';
	}

	return (in);
}

/**
 * shell_loop - shell loop
 * @datash: relevant data
 *
 * Return: no return.
 */
void shell_loop(data_shell *datash)
{
	int l_oop, i_eof;
	char *input;

	l_oop = 1;
	while (l_oop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			l_oop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			l_oop = 0;
			free(input);
		}
	}
}
