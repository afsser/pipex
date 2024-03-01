#ifndef PIPEX_H
# define PIPEX_H

# include "../../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>  
# include <stdlib.h>

typedef struct s_pipex	t_pipex;
struct					s_pipex
{
	int		nb_cmd;
	int		nb_cmd_curr;
	int		fd_in;
	int		fd_out;
	int		ac;
	int		*fd;
	char	**av;
	char	**paths;
	char	**paths_temp;
	char	**envp;
	char	**cmd;
	pid_t	pid;
	pid_t	pid_2;
};

void	failure(char *error_msg, t_pipex *pipex, int flag);

#endif