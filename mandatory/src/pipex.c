/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:21:33 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/03/16 18:23:01 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void get_path(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (!ft_strnstr(pipex->envp[i], "PATH=", 5))
		i++;
	pipex->paths_temp = ft_split(pipex->envp[i] + 5, ':');
	if (pipex->paths_temp == NULL)
	// if (1)
		failure("Pipex failed to split paths. ", pipex, 1);
	i = 0;
	while (pipex->paths_temp[i])
		i++;
	pipex->paths = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (pipex->paths_temp[++i])
		pipex->paths[i] = ft_strjoin(pipex->paths_temp[i], "/");
	pipex->paths[i] = NULL;
	i = -1;
	while (pipex->paths_temp[++i])
		free(pipex->paths_temp[i]);
	free(pipex->paths_temp);
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
		close(pipex->fd[0]);
		dup2(pipex->fd[1], STDOUT_FILENO);
		
		close(pipex->fd[1]);
	}
	else
	{
		close(pipex->fd[1]);
		waitpid(pipex->pid, NULL, 0);
		
		close(pipex->fd[0]);
	}
}