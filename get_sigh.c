#include "main.h"

/**
 * get_sigint - call in prompt
 * @sig: Sig handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
