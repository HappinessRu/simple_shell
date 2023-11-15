#include "main.h"

/**
 * add_rvar_node - add a var
 * @head: head
 * @lvar: len of var
 * @val: value of var
 * @lval: len of value.
 * Return: address of head.
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_rvar_list - free r_var list
 * @head: head
 * Return: none
 */
void free_rvar_list(r_var **head)
{
	r_var *tem;
	r_var *cu_r;

	if (head != NULL)
	{
		cu_r = *head;
		while ((tem = cu_r) != NULL)
		{
			cu_r = cu_r->next;
			free(tem);
		}
		*head = NULL;
	}
}
