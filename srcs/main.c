/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:02:24 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/08 20:47:04 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

// void	ft_print_double_chararr(char **arr, int	n)
// {
// 	int i;

// 	i = 0;
// 	while (i < n)
// 		printf("%s\n", arr[i++]);
// }

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

void	ft_child(int cmd_i, t_pipex *pipex)
{
	dup2(ft_set_stdin(cmd_i, pipex), STDIN_FILENO);
	dup2(ft_set_stdout(cmd_i, pipex), STDOUT_FILENO);
	ft_close_all_fds(pipex);
	if (execve(pipex->newargvs[cmd_i][0], pipex->newargvs[cmd_i], NULL) == -1)
		ft_exit(500 + 1, pipex);
}

int	main(int argc, char **argv, char **envp)
{
	int		pid;
	t_pipex	pipex;
	int cmd_i;

	ft_make_pipex(argc, argv, envp, &pipex);
	cmd_i = 0;
	while (cmd_i < pipex.cmd_num)
	{
		pid = fork();
		if (pid == -1)
			ft_exit(400 + 1, &pipex);
		if (pid == 0)
			ft_child(cmd_i, &pipex);
		cmd_i++;
	}
	wait(NULL);
	ft_clean_pipex(&pipex);
	return 0;
}
