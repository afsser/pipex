/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:21:28 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/03/16 18:22:17 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static t_pipex	init(void)
{
	t_pipex	pipex;

	pipex.fd_in = -1;
	pipex.fd_out = -1;
	pipex.nb_cmd = 0;
	pipex.nb_cmd_curr = 2;
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
	pipex.nb_cmd = argc - 3;
	return (pipex);
}