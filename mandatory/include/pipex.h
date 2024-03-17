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

# define CLEAN	1
# define END	0

typedef struct s_pipex	t_pipex;
struct					s_pipex
{
	int		curr_cmd;
	int		fd_in;
	int		fd_out;
	int		ac;
	int		*fd;
	char	**av;
	char	**paths;
	char	**paths_temp;
	char	**envp;
	char	**cmd;
	pid_t	pid1;
	pid_t	pid2;
};

t_pipex	fill_data(int argc, char **argv, char **envp, int *fd);
void	get_path(t_pipex *pipex);
void	parse_cmd(t_pipex *pipex);
void	fork_init(t_pipex *pipex);
void	ft_free(t_pipex *pipex);
void	failure(char *error_msg, t_pipex *pipex, int free_flag);

#endif