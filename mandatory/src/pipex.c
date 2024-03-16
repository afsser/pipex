/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:21:33 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/03/16 19:51:37 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void ft_command(t_pipex *pipex)
{
	int		i;
	char	*cmd;
	
	// if (pipex->pid == 0)
	// 	ft_printf("CHEGOU NA CRIANÇA\n");
	// if (pipex->pid > 0)
	// 	ft_printf("CHEGOU NO PAI\n");
		
	get_cmd(pipex);
	i = 0;
	while (pipex->paths[i])
	{
		cmd = ft_strjoin(pipex->paths[i], (const char *)pipex->cmd[0]);
		if (access(cmd, F_OK) == 0
			&& execve(cmd, pipex->cmd, pipex->envp) == -1)
		{
			free(cmd);
			failure("Error executing cmd\n", pipex, 1);
		}
		free(cmd);
		i++;
	}
	failure("Error to find path\n", pipex, 1);
}

static void	child_process(t_pipex *pipex)
{
	dup2(pipex->fd[1], STDOUT_FILENO);
	dup2(pipex->fd_in, STDIN_FILENO);
	close(pipex->fd[0]);
	ft_command(pipex);
}

static void	parent_process(t_pipex *pipex)
{
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(pipex->fd_out, STDOUT_FILENO);
	close(pipex->fd[1]);
	ft_command(pipex);
}

void fork_init(t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		failure("Failed to fork\n", pipex, 1);
	}
	if (pipex->pid == 0)
	{
		// ft_printf("CHEGOU NA CRIANÇA\n");
		child_process(pipex);
	}
	waitpid(pipex->pid, NULL, 0);
	// ft_printf("CHEGOU NO PAI\n");
	parent_process(pipex);
}
