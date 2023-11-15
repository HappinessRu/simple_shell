#include "main.h"

/**
 * check_env - env variable
 * @h: head
 * @in: input str
 * @data: data
 * Return: none
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int r_ow, chr, m, val;
	char **_envr;

	_envr = data->_environ;
	for (r_ow = 0; _envr[r_ow]; r_ow++)
	{
		for (m = 1, chr = 0; _envr[r_ow][chr]; chr++)
		{
			if (_envr[r_ow][chr] == '=')
			{
				val = _strlen(_envr[r_ow] + chr + 1);
				add_rvar_node(h, m, _envr[r_ow] + chr + 1, val);
				return;
			}

			if (in[m] == _envr[r_ow][chr])
				m++;
			else
				break;
		}
	}

	for (m = 0; in[m]; m++)
	{
		if (in[m] == ' ' || in[m] == '\t' || in[m] == ';' || in[m] == '\n')
			break;
	}

	add_rvar_node(h, m, NULL, 0);
}

/**
 * check_vars - typed variable
 * @h: head
 * @in: input
 * @st: status
 * @data: data
 * Return: none
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int z, ls_t, lp_d;

	ls_t = _strlen(st);
	lp_d = _strlen(data->pid);

	for (z = 0; in[z]; z++)
	{
		if (in[z] == '$')
		{
			if (in[z + 1] == '?')
				add_rvar_node(h, 2, st, ls_t), z++;
			else if (in[z + 1] == '$')
				add_rvar_node(h, 2, data->pid, lp_d), z++;
			else if (in[z + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[z + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[z + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[z + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[z + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + z, data);
		}
	}

	return (z);
}

/**
 * replaced_input - replaces string into var
 * @head: head
 * @input: input
 * @new_input: new input string
 * @nlen: length
 * Return: replaced str
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int z, m, a;

	indx = *head;
	for (m = z = 0; z < nlen; z++)
	{
		if (input[m] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[z] = input[m];
				m++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (a = 0; a < indx->len_var; a++)
					m++;
				z--;
			}
			else
			{
				for (a = 0; a < indx->len_val; a++)
				{
					new_input[z] = indx->val[a];
					z++;
				}
				m += (indx->len_var);
				z--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[z] = input[m];
			m++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls functions
 * @input: input
 * @datash: data
 * Return: replaced str
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int ol_en, nl_en;

	status = aux_itoa(datash->status);
	head = NULL;

	ol_en = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nl_en = 0;

	while (indx != NULL)
	{
		nl_en += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nl_en += ol_en;

	new_input = malloc(sizeof(char) * (nl_en + 1));
	new_input[nl_en] = '\0';

	new_input = replaced_input(&head, input, new_input, nl_en);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
