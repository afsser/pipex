/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:14:11 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/03/01 19:06:10 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

//   -------------  PASSAR ARGUMENTOS (COMANDO) (FLAGS) (AMBIENT VARIABLES)

#define READ_BUFFER_SIZE 100

void	get_path(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (!ft_strnstr(pipex->envp[i], "PATH=", 5))
		i++;
	pipex->paths_temp = ft_split(pipex->envp[i] + 5, ':');
	if (pipex->paths_temp == NULL)
		failure("Pipex failed to split paths. ", &pipex, 0);
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

t_pipex	init(void)
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

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	// pid_t	pid;
	// char	buffer[READ_BUFFER_SIZE];
	// ssize_t	bytesRead;
	t_pipex	pipex;
	
	if (argc != 5)
	{
		ft_printf("Args expected format:\n<infile> <cmd1> <cmd2> <outfile>\n");
		exit(EXIT_FAILURE);
	}
	if (!envp)
		failure("Failed to get ENVP.", &pipex, 0);
	if (pipe(fd) == -1)
	{
		failure("Pipex failed to execute pipe().", &pipex, 1);
		return (0);
	}
	pipex = fill_data(argc, argv, envp, fd);
	get_path(&pipex);
	ft_free(&pipex);
	
	// pid = fork();
	// if (pid == -1)
	// {
	// 	perror("Failed to fork\n");
	// 	return (EXIT_FAILURE);
	// }
	// if (pid == 0)
	// {
	// 	close(fd[0]);
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	ft_printf("Hi Parent");
	// 	close(fd[1]);
	// 	return (EXIT_SUCCESS);
	// }
	// else
	// {
	// 	close(fd[1]);
	// 	waitpid(pid, NULL, 0);
	// 	bytesRead = read(fd[0], buffer, sizeof(buffer) - 1);
	// 	buffer[bytesRead] = '\0';
	// 	ft_printf("Message from child: %s\n", buffer);
	// 	close(fd[0]);
	// 	return (EXIT_SUCCESS);
	// }


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