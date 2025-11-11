#include "pipex.h"

void	error_msg(const char *msg)
{
	size_t	len;

	len = 0;
	while (msg[len] != '\0')
		len++;
	write(2, "Error: ", 7);
	write(2, msg, len);
	write(2, "\n", 1);
}

void	error_perror(const char *msg)
{
	perror(msg);
}

