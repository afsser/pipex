/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:14:11 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/03/17 19:01:33 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	open_file(t_pipex *pipex)
{
	pipex->fd_in = open(pipex->av[1], O_RDONLY);
	pipex->fd_out = open(pipex->av[pipex->ac - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_in < 0)
	{
		if (pipex->fd_out >= 0)
			close(pipex->fd_out);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		failure("Error while open infile\n", pipex, CLEAN);
	}
	if (pipex->fd_out < 0)
	{
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		close(pipex->fd_in);
		failure("Error while deal with outfile\n", pipex, CLEAN);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	t_pipex	pipex;
	
	if (argc != 5)
		failure("Args expected format:\n<infile> <cmd1> <cmd2> <outfile>\n", &pipex, END);
	if (!envp)
		failure("Failed to get ENVP.", &pipex, END);
	if (pipe(fd) == -1)
	{
		failure("Pipex failed to execute pipe().", &pipex, END);
		return (1);
	}
	pipex = fill_data(argc, argv, envp, fd);
	open_file(&pipex);
	get_path(&pipex);
	fork_init(&pipex);
	close(fd[0]);
	close(fd[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	close(pipex.fd_in);
	close(pipex.fd_out);
	ft_free(&pipex);
	return (0);
}
