#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft.h"

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


int	main(int argc, char **argv)
{
	int		pid;
	int		pp[2];
	int		fd1;
	int		fd2;
	// char	*cmd1;
	// char	*cmd2;
	char	*file1;
	char	*file2;
	char	**argv1;
	char	**argv2;
	// int		argc1;
	// int		argc2;

	ft_check_input(argc); /////////////////////////////////////
	
	file1 = argv[1];
	file2 = argv[4];

	// argc1 = ft_toknum(argv[2], ' ');
	// argc2 = ft_toknum(argv[3], ' ');
	// argv1 = ft_split(argv[2], ' ');
	// argv2 = ft_split(argv[3], ' ');
	// cmd1 = argv1[0];
	// cmd2 = argv2[0];

	argv1 = ft_make_newargv(argv[2]);
	argv2 = ft_make_newargv(argv[3]);
	ft_print_double_chararr(argv1, ft_toknum(argv[2], ' ') + 1);
	ft_print_double_chararr(argv2, ft_toknum(argv[2], ' ') + 1);

	if (pipe(pp) == -1)
		printf("Failed to pipe.\n");

	fd1 = open(file1, O_RDONLY);
	fd2 = open(file2, O_CREAT | O_WRONLY, 0777);
	printf("fd%d = %s\n", fd1, argv[1]);
	printf("fd%d = %s\n", fd2, argv[4]);

	pid = fork();
	if (pid == -1)
	{
		printf("Can't fork process: %s\n", strerror(errno));
		return 1;
	}

	if (!pid)
	{
		dup2(fd1, STDIN_FILENO);
		dup2(pp[1], STDOUT_FILENO);
		close(fd1);
		close(fd2);
		close(pp[0]);
		// if (execl(cmd1, cmd1, NULL) == -1) {
		if (execve(argv1[0], argv1, NULL) == -1) {
			printf("Child exec failed.\n"); /////////////////////////////////////////
		}
	}
	else
	{
		dup2(pp[0], STDIN_FILENO);
		close(pp[0]);
		close(pp[1]);
		close(fd1);
		
		wait(NULL);
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
		// if (execl(cmd2, cmd2, NULL) == -1) {
		if (execve(argv2[0], argv2, NULL) == -1) {
			printf("Parent exec failed.\n"); /////////////////////////////////////////
		}

		// char str[1000];
		// read(0, &str, 1000);
		// // write(1, &str, 1000);
		// printf("%s\n", str);

		// free newargv < ft_split


	}
	return 0;
}
