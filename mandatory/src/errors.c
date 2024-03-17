/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:21:41 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/03/17 19:00:20 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	failure(char *error_msg, t_pipex *pipex, int free_flag)
{
	if (free_flag == CLEAN)
	{
		close(pipex->fd_in);
		close(pipex->fd_out);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		ft_free(pipex);
	}
	ft_printf(error_msg);
	exit(EXIT_FAILURE);
}