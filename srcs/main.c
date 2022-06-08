/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:02:24 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/08 21:28:09 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

void	ft_init_pipex(t_pipex *pipex)
{
	pipex->cmd_num = 0;
	pipex->pipe_num = 0;
	pipex->fd1 = -1;
	pipex->fd2 = -1;
	pipex->paths = NULL;
	pipex->pipes = NULL;
	pipex->newargvs = NULL;
}

void	ft_make_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	if (argc != 5)
		write(2, "Error: wrong input format\n", 26);
	ft_init_pipex(pipex);
	pipex->cmd_num = argc - 3;
	pipex->pipe_num = pipex->cmd_num - 1;
	pipex->fd1 = open(argv[1], O_RDONLY);
	if (pipex->fd1 < 0)
		ft_exit(100 + 1, pipex);
	pipex->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY, 0777);
	if (pipex->fd2 < 0)
		ft_exit(100 + 2, pipex);
	ft_make_paths(envp, pipex);
	ft_make_newarvs(argv, pipex);
	ft_make_pipes(pipex);
	ft_find_cmds(pipex);
}

int	main(int argc, char **argv, char **envp)
{
	int		pid;
	t_pipex	pipex;
	int		cmd_i;

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
	return (0);
}
