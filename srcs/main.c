/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:02:24 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/08 11:40:11 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

void	ft_print_double_chararr(char **arr, int	n)
{
	int i;

	i = 0;
	while (i < n)
		printf("%s\n", arr[i++]);
}

/*	A command reads from the pipe[0] of preceding index
	if it is not the FIRST one which reads from file1 (fd1) */
int	ft_set_stdin(int cmd_i, t_pipex *pipex)
{
	if (cmd_i == 0)
		return (pipex->fd1);
	else
		return (pipex->pipes[cmd_i-1][0]);
}

/*	A command writes to the pipe[1] of the same index
	if it is not the LAST one which writes to file2 (fd2) */
int	ft_set_stdout(int cmd_i, t_pipex *pipex)
{
	if (cmd_i == pipex->cmd_num - 1)
		return (pipex->fd2);
	else
		return (pipex->pipes[cmd_i][1]);
}

int	main(int argc, char **argv, char **env)
{
	int		pid;
	t_pipex	pipex;
	int i;

	ft_init_pipex(argc, argv, &pipex);
	i = 0;
	while (i < pipex.cmd_num)
	{
		pid = fork();
		if (pid == -1)
		{
			printf("Can't fork process: %s\n", strerror(errno)); /////////////////////////////////////////
			return 1; /////////////////////////////////////////
		}
		if (pid == 0)
		{
			dup2(ft_set_stdin(i, &pipex), STDIN_FILENO);
			dup2(ft_set_stdout(i, &pipex), STDOUT_FILENO);
			ft_close_all_fds(&pipex);
			if (execve(pipex.newargvs[i][0], pipex.newargvs[i], NULL) == -1)
				printf("Child %d exec failed.\n", i); /////////////////////////////////////////
		}
		i++;
	}
	ft_clean_pipex(&pipex);
	return 0;
}
