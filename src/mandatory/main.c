
#include "pipex.h"

//   -------------  PASSAR ARGUMENTOS (COMANDO) (FLAGS) (AMBIENT VARIABLES)

int	main(int argc, char **argv)
{
	// pid_t	pid;
	// pid = fork();
	// if (pid == -1)
	// {
	// 	ft_printf("Failed to fork\n");
	// 	return (1);
	// }
	// if (pid > 0)
	// {
	// 	ft_printf("This is the Parent Process\n");
	// }
	// else
	// {
	// 	ft_printf("This is the Child Process\n");
	// }


	char	**args;
	if (argc == 2) // deve ser 5
	{
		args = ft_split(argv[1], ' ');
		execve("/bin/ls", args, NULL);
	}
		// write(1, "error", 5);
	

	ft_printf("ta funcionando %s\n", ft_strdup("sim"));
	ft_printf("5 + 5 = %d\n", ft_strlen("0123456789"));
	ft_printf("%c\n", ft_toupper('a'));
	ft_printf("%s\n", ft_strjoin("hello ", "world"));
	return (0);
}
