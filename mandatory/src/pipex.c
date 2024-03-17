/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:21:33 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/03/17 19:13:42 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void ft_command(t_pipex *pipex)
{
	int		i;
	char	*cmd;

	parse_cmd(pipex);
	i = 0;
	while (pipex->paths[i])
	{

		cmd = ft_strjoin(pipex->paths[i], (const char *)pipex->cmd[0]);
		if (access(cmd, F_OK) == 0
			&& execve(cmd, pipex->cmd, pipex->envp) == -1)
		{
			free(cmd);
			failure("Error executing cmd\n", pipex, CLEAN);
		}
		free(cmd);
		i++;
	}
	failure("Error to find path\n", pipex, CLEAN);
}

static void	child1_process(t_pipex *pipex)
{
	dup2(pipex->fd[1], STDOUT_FILENO);
	dup2(pipex->fd_in, STDIN_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	ft_command(pipex);
}

static void	child2_process(t_pipex *pipex)
{
	pipex->curr_cmd++;
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(pipex->fd_out, STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	ft_command(pipex);
}

void fork_init(t_pipex *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{
		failure("Failed to fork\n", pipex, CLEAN);
	}
	if (pipex->pid1 == 0)
	child1_process(pipex);
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
	{
		failure("Failed to fork\n", pipex, CLEAN);
	}
	if (pipex->pid2 == 0)
		child2_process(pipex);
}
