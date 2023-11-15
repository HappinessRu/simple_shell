#include "main.h"

/**
 * add_sep_node_end - adds A separator
 * @head: head
 * @sep: separator
 * Return: address
 */
sep_list *add_sep_node_end(sep_list **head, char sep)
{
	sep_list *new, *tem;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	tem = *head;

	if (tem == NULL)
	{
		*head = new;
	}
	else
	{
		while (tem->next != NULL)
			tem = tem->next;
		tem->next = new;
	}

	return (*head);
}

/**
 * free_sep_list - free sep_list
 * @head: head
 * Return: none
 */
void free_sep_list(sep_list **head)
{
	sep_list *tem;
	sep_list *cu_r;

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

/**
 * add_line_node_end - adds a command line
 * @head: head
 * @line: line.
 * Return: address
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *tem;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	tem = *head;

	if (tem == NULL)
	{
		*head = new;
	}
	else
	{
		while (tem->next != NULL)
			tem = tem->next;
		tem->next = new;
	}

	return (*head);
}

/**
 * free_line_list - free line_list
 * @head: head
 * Return: none
 */
void free_line_list(line_list **head)
{
	line_list *tem;
	line_list *cu_r;

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
