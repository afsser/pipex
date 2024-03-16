/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:14:11 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/03/16 18:22:55 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	t_pipex	pipex;
	
	if (argc != 5)
	{
		failure("Args expected format:\n<infile> <cmd1> <cmd2> <outfile>\n", &pipex, 0);
		// ft_printf("Args expected format:\n<infile> <cmd1> <cmd2> <outfile>\n");
		exit(EXIT_FAILURE);
	}
	if (!envp)
		failure("Failed to get ENVP.", &pipex, 0);
	if (pipe(fd) == -1)
	{
		failure("Pipex failed to execute pipe().", &pipex, 0);
		return (1);
	}
	pipex = fill_data(argc, argv, envp, fd);
	get_path(&pipex);
	fork_init(&pipex);
	ft_free(&pipex);
	



	// char	**args;
	// if (argc == 2) // deve ser 5
	// {
	// 	args = ft_split(argv[1], ' ');
	// 	execve("/bin/ls", args, NULL);
	// }
	// else
	// {
	// 	ft_printf("No args passed\n");
	// }
	
	// ft_printf("fd[0] : %d\n", fd[0]);
	// ft_printf("fd[1] : %d\n", fd[1]);
	// ft_printf("ta funcionando %s\n", ft_strdup("sim"));
	// ft_printf("5 + 5 = %d\n", ft_strlen("0123456789"));
	// ft_printf("%c\n", ft_toupper('a'));
	// ft_printf("%s\n", ft_strjoin("hello ", "world"));
	return (0);
}

	// int		i;

	// i = 0;
	// while (pipex.paths[i])
	// {
	// 	ft_printf("%s\n", pipex.paths[i]);
	// 	i++;
	// }