/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:21:28 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/03/17 15:06:31 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static t_pipex	init(void)
{
	t_pipex	pipex;

	pipex.fd_in = -1;
	pipex.fd_out = -1;
	pipex.ac = -1;
	pipex.av = NULL;
	pipex.paths = NULL;
	pipex.paths_temp = NULL;
	pipex.envp = NULL;
	pipex.cmd = NULL;
	pipex.fd = NULL;
	return (pipex);
}

t_pipex fill_data(int argc, char **argv, char **envp, int *fd)
{
	t_pipex	pipex;

	pipex = init();
	pipex.ac = argc;
	pipex.av = argv;
	pipex.envp = envp;
	pipex.fd = fd;
	return (pipex);
}

void get_cmd(t_pipex *pipex)
{
	int		i;
	char	*temp;

	if (pipex->pid == 0)
		pipex->cmd = ft_split(pipex->av[2], ' ');
	else if (pipex->pid > 0)
		pipex->cmd = ft_split(pipex->av[3], ' ');
	if (!pipex->cmd)
		failure("Error spliting cmd\n", pipex, 1);
	i = -1;
	temp = NULL;
	while (pipex->cmd[++i])
	{
		temp = pipex->cmd[i];
		pipex->cmd[i] = ft_strtrim(pipex->cmd[i], "'");
		free(temp);
	}
}

void get_path(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (!ft_strnstr(pipex->envp[i], "PATH=", 5))
		i++;
	pipex->paths_temp = ft_split(pipex->envp[i] + 5, ':');
	if (pipex->paths_temp == NULL)
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
