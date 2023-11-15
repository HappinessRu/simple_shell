#include "main.h"

/**
 * bring_line - assign line var for get_line
 * @lineptr: lineptr
 * @buffer: buffer
 * @n: n
 * @j: j
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Read input from stream
 * @lineptr: lineptr
 * @n: n
 * @stream: stream
 * Return: bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int z;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char b = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (b != '\n')
	{
		z = read(STDIN_FILENO, &b, 1);
		if (z == -1 || (z == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (z == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = b;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (z != 0)
		input = 0;
	return (retval);
}
