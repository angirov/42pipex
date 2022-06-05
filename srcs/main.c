#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft.h"

typedef	struct s_pipex
{
	int		cmd_num;
	int		pipe_num;
	int		**pipes;
	char	***newargvs;
	char	*file1;
	char	*file2;
	int		fd1;
	int		fd2;
}	t_pipex;

int	ft_check_input(int argc)
{
	if (argc == 5)
		return (0);
	perror(strerror(errno));
	exit(1);
}

char	**ft_make_newargv(char *arg_string)
{
	int		newargc;
	char	*newstring;
	char	**newargv;

	newargc = ft_toknum(arg_string, ' ');
	newstring = ft_strjoin(arg_string, " NULL");
	newargv = ft_split(newstring, ' ');
	free(newstring);
	free(newargv[newargc]);
	newargv[newargc] = NULL;
	return (newargv);
}

/* Do not forget that some of double char arrays may have a the last slot pointing to NULL */
void	ft_free_double_chararr(char **arr, int	n)
{
	int i;

	i = 0;
	while (i++ < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_print_double_chararr(char **arr, int	n)
{
	int i;

	i = 0;
	while (i < n)
		printf("%s\n", arr[i++]);
}

void	ft_init_pipex(int argc, char **argv, t_pipex *pipex)
{
	pipex->fd1 = open(argv[1], O_RDONLY);
	pipex->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY, 0777);
	printf("fd%d = %s\n", pipex->fd1, argv[1]);
	printf("fd%d = %s\n", pipex->fd2, argv[argc - 1]);

	pipex->cmd_num = argc - 3;
	pipex->pipe_num = pipex->cmd_num - 1;
	printf("cmd_num = %d\n", pipex->cmd_num);
	printf("pipe_num = %d\n", pipex->pipe_num);

	pipex->pipes = malloc(sizeof(int *) * pipex->pipe_num);
	int	i;
	i = 0;
	int pipe_res;
	while (i < pipex->pipe_num)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		pipe_res = pipe(pipex->pipes[i]);
		if (pipe_res == -1)
			printf("Failed to pipe %d.\n", i); ///////////////////////////////////////////////////////
		i++;
	}

	pipex->newargvs = malloc(sizeof(char **) * pipex->cmd_num);
	i = 0;
	while (i < pipex->cmd_num)
	{
		pipex->newargvs[i] = ft_make_newargv(argv[i + 2]);
		i++;
	}
}
void	ft_close_fds(int cmd_i, t_pipex *pipex)
{
	close(pipex->fd1);
	close(pipex->fd2);
	int j;
	j = 0;
	while (j < pipex->pipe_num)
	{
		if (j != cmd_i - 1 || cmd_i == 0)
			close(pipex->pipes[j][0]);
		if (j != cmd_i || cmd_i == pipex->cmd_num - 1)
			close(pipex->pipes[j][1]);
		if (cmd_i != 0)
			close(pipex->fd1);
		if (cmd_i != pipex->cmd_num - 1)
			close(pipex->fd2);
		j++;
	}
}

// int	ft_set_stdin(int i, t_pipex pipex)
// int	ft_set_stdout(int i, t_pipex pipex)


int	main(int argc, char **argv)
{
	int		pid;
	t_pipex	pipex;

	ft_check_input(argc); /////////////////////////////////////
	ft_init_pipex(argc, argv, &pipex);

	int i;
	i = 0;
	while (i < pipex.cmd_num)
	{
		pid = fork();
		if (pid == -1)
		{
			printf("Can't fork process: %s\n", strerror(errno));
			return 1;
		}
		if (pid == 0)
		{
			// if (i > 0)
			// 	sleep(2);
			printf("Hello from child %d\n", i);
			ft_print_double_chararr(pipex.newargvs[i], ft_toknum(argv[i + 2] + 1, ' '));
			// int	ft_set_stdin(int i, t_pipex pipex)
			// int	ft_set_stdout(int i, t_pipex pipex)
			if (i == 0)
				dup2(pipex.fd1, STDIN_FILENO);
			else
				dup2(pipex.pipes[i-1][0], STDIN_FILENO);
			if (i == pipex.cmd_num - 1)
				dup2(pipex.fd2, STDOUT_FILENO);
			else
				dup2(pipex.pipes[i][1], STDOUT_FILENO);
			ft_close_fds(i, &pipex);
			if (execve(pipex.newargvs[i][0], pipex.newargvs[i], NULL) == -1)
				printf("Child %d exec failed.\n", i); /////////////////////////////////////////
		}
		i++;
	}
	// else
	// {
	// 	dup2(pp[0], STDIN_FILENO);
	// 	close(pp[0]);
	// 	close(pp[1]);
	// 	close(fd1);
		
	// 	wait(NULL);
	// 	dup2(fd2, STDOUT_FILENO);
	// 	close(fd2);
	// 	// if (execl(cmd2, cmd2, NULL) == -1) {
	// 	if (execve(argv2[0], argv2, NULL) == -1) {
	// 		printf("Parent exec failed.\n"); /////////////////////////////////////////
	// 	}

		// char str[1000];
		// read(0, &str, 1000);
		// // write(1, &str, 1000);
		// printf("%s\n", str);

		// free newargv < ft_split
	return 0;
}
