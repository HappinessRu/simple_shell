#include "main.h"

/**
 * swap_char - swaps | and &
 * @input: input
 * @bool: bool
 * Return: swapped str
 */
char *swap_char(char *input, int bool)
{
	int z;

	if (bool == 0)
	{
		for (z = 0; input[z]; z++)
		{
			if (input[z] == '|')
			{
				if (input[z + 1] != '|')
					input[z] = 16;
				else
					z++;
			}

			if (input[z] == '&')
			{
				if (input[z + 1] != '&')
					input[z] = 12;
				else
					z++;
			}
		}
	}
	else
	{
		for (z = 0; input[z]; z++)
		{
			input[z] = (input[z] == 16 ? '|' : input[z]);
			input[z] = (input[z] == 12 ? '&' : input[z]);
		}
	}
	return (input);
}

/**
 * add_nodes - add separators
 * @head_s: head
 * @head_l: head
 * @input: input str
 * Return: none
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int z;
	char *line;

	input = swap_char(input, 0);

	for (z = 0; input[z]; z++)
	{
		if (input[z] == ';')
			add_sep_node_end(head_s, input[z]);

		if (input[z] == '|' || input[z] == '&')
		{
			add_sep_node_end(head_s, input[z]);
			z++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - next command line stored
 * @list_s: list
 * @list_l: line list
 * @datash: data struct
 * Return: nonone
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sp;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sp = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sp)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sp = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sp = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sp)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - splits command line
 * @datash: data struct
 * @input: input str
 * Return: 0 to exit
 */
int split_commands(data_shell *datash, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int l_oop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		l_oop = exec_line(datash);
		free(datash->args);

		if (l_oop == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (l_oop == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes input str
 * @input: input str
 * Return: string splitted
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}

