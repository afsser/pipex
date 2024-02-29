/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:14:11 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/02/29 15:47:15 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//   -------------  PASSAR ARGUMENTOS (COMANDO) (FLAGS) (AMBIENT VARIABLES)

int	main(int argc, char **argv)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		ft_printf("Child process (PID %d) executing...\n", getpid());
        sleep(2);
        ft_printf("Child process ending...\n");
        sleep(1);
        exit(42);
		// close(fd[1]);
		// dup2(fd[0], 0);
	}
	if (pid > 0)
	{
		int		status;
		pid_t	child_pid;

		child_pid = wait(&status);
		ft_printf("Parent process (PID %d) waiting for child process (PID %d)...\n", getpid(), pid);
		if (WIFEXITED(status))
			ft_printf("Child Process (PID %d) killed. Code: %d.\n", child_pid, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			ft_printf("Child process (PID %d) killed by signal %d.\n", child_pid, WTERMSIG(status));
        sleep(1);
		ft_printf("Parent Process Ending\n");
        sleep(1);
		// close(fd[0]);
		// dup2(fd[1], 1);
	}
	else
	{
		perror("fork error:");
		return (1);
	}


	char	**args;
	if (argc == 2) // deve ser 5
	{
		args = ft_split(argv[1], ' ');
		execve("/bin/ls", args, NULL);  // como atribuir o endereço para o comando correto ??
	}
		perror("Argument error");
	
	return (0);
}
