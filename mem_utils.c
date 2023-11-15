#include "main.h"

/**
 * _memcpy - copies information
 * @newptr: pointer.
 * @ptr: ptr.
 * @size: size
 * Return: none.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int z;

	for (z = 0; z < size; z++)
		char_newptr[z] = char_ptr[z];
}

/**
 * _realloc - reallocates memory
 * @ptr: pointer
 * @old_size: size
 * @new_size: new size
 * Return: ptr.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp - reallocates memory
 * @ptr: ptr
 * @old_size: size
 * @new_size: new size
 * Return: ptr.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int z;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (z = 0; z < old_size; z++)
		newptr[z] = ptr[z];

	free(ptr);

	return (newptr);
}
