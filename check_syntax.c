#include "main.h"

/**
 * repeated_char - counts repetitions of a char
 *
 * @input: input
 * @i: index
 * Return: repetitions
 */
int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - identifies syntax errors
 *
 * @input: input
 * @i: index
 * @last: last character read
 * Return: index of error. 0 (no errors)
 */
int error_sep_op(char *input, int i, char last)
{
	int co_unt;

	co_unt = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			co_unt = repeated_char(input, 0);
			if (co_unt == 0 || co_unt > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			co_unt = repeated_char(input, 0);
			if (co_unt == 0 || co_unt > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - identifies index of the first char
 *
 * @input: input
 * @i: index
 * Return: 1 if there is an error. 0 (no error)
 */
int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - shows where a syntax error is found
 *
 * @datash: data struct
 * @input: input
 * @i: index
 * @bool: to control msg error
 * Return: none
 */
void print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	char *msg_one, *msg_two, *msg_three, *err, *counter;
	int len;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg_one = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg_one = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg_one = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg_one = (input[i + 1] == '&' ? "&&" : "&");

	msg_two = ": Syntax error: \"";
	msg_three = "\" unexpected\n";
	counter = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(counter);
	len += _strlen(msg_one) + _strlen(msg_two) + _strlen(msg_three) + 2;

	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(counter);
		return;
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, counter);
	_strcat(err, msg_two);
	_strcat(err, msg_one);
	_strcat(err, msg_three);
	_strcat(err, "\0");

	write(STDERR_FILENO, err, len);
	free(err);
	free(counter);
}

/**
 * check_syntax_error - find and print a syntax error
 *
 * @datash: data struct
 * @input: input
 * Return: 1 if there is an error. 0 (no error)
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int start = 0;
	int f = 0;
	int z = 0;

	f = first_char(input, &start);
	if (f == -1)
	{
		print_syntax_error(datash, input, start, 0);
		return (1);
	}

	z = error_sep_op(input + start, 0, *(input + start));
	if (z != 0)
	{
		print_syntax_error(datash, input, start + z, 1);
		return (1);
	}

	return (0);
}
