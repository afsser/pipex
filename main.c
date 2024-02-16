#include <unistd.h>

#include <string.h>
#include <stdlib.h>

//   -------------  PASSAR ARGUMENTOS (COMANDO) (FLAGS) (AMBIENT VARIABLES)

int	main(int argc, char **argv)
{
	int		len;
	int		i;
	int		j;
	char	**args;

	len = 0;
	while(argv[len])
		len++;
	args = malloc((len - 1) * sizeof(char *));
	i = 1;
	j = 0;
	while(i < len - 1)
		args[j++] = argv[i++];
	if (argc >= 4) // deve ser 5
	{
		execve("/bin/ls", args, NULL);
	}
	write(1, "error", 5);
}
