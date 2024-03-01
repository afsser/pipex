#include "../include/pipex.h"

void	ft_free(t_pipex *pipex)
{
	int	i;

	i = -1;
	if (pipex->paths != NULL)
	{
		while (pipex->paths[++i])
		{
			free(pipex->paths[i]);
			pipex->paths[i] = NULL;
		}
		free(pipex->paths);
		pipex->paths = NULL;
	}
	i = -1;
	if (pipex->cmd != NULL)
	{
		while (pipex->cmd[++i])
		{
			free(pipex->cmd[i]);
			pipex->cmd[i] = NULL;
		}
		free(pipex->cmd);
		pipex->cmd = NULL;
	}
}

void	failure(char *error_msg, t_pipex *pipex, int flag)
{
	if (flag == 1)
	{
		close(pipex->fd_in);
		close(pipex->fd_out);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		ft_free(pipex);
	}
	perror(error_msg);
	exit(EXIT_FAILURE);
}