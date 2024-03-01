#include "pipex.h"

void	failure(char *error_msg, t_pipex *pipex, int flag)
{
	if (flag == 1)
	{
		close(pipex->fd_in);
		close(pipex->fd_out);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	perror(error_msg);
	exit(EXIT_FAILURE);
}