/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_app.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:25:26 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/23 11:27:13 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

/* Initializing information from the OUTER input sourse */
void	ft_init_pipex(int argc, char **argv,  char **envp, t_pipex *pipex)
{
	pipex->envp = envp;
	pipex->cmd_num = argc - 3;
	pipex->pipe_num = 0;
	pipex->infile_name = argv[1];
	pipex->outfile_name = argv[argc - 1];
	pipex->pipe_num = pipex->cmd_num - 1;
	pipex->fd1 = -1;
	pipex->fd2 = -1;
	pipex->paths = NULL;
	pipex->pipes = NULL;
	pipex->newargvs = NULL;
}

void	ft_make_newarvs(char **argv, t_pipex *pipex)
{
	int	i;

	pipex->newargvs = malloc(sizeof(char **) * pipex->cmd_num);
	i = 0;
	while (i < pipex->cmd_num)
	{
		pipex->newargvs[i] = ft_split(argv[i + 2], ' ');
		i++;
	}
}

void	ft_make_paths(t_pipex *pipex)
{
	char	**envp;

	envp = pipex->envp;
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	if (ft_strncmp("PATH", *envp, 4))
		ft_exit(50, pipex);
	pipex->paths = ft_split(*envp + 5, ':');
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		write(2, "Error: wrong input format\n", 26);
	ft_init_pipex(argc, argv, envp, &pipex);
	ft_make_newarvs(argv, &pipex);
	// ft_make_pipex(&pipex);
	// cmd_i = 0;
	// while (cmd_i < pipex.cmd_num)
	// {
	// 	pid = fork();
	// 	if (pid == -1)
	// 		ft_exit(400 + 1, &pipex);
	// 	if (pid == 0)
	// 		ft_child(cmd_i, &pipex);
	// 	cmd_i++;
	// }
	// wait(NULL);
	// ft_clean_pipex(&pipex);
	ft_pipex(&pipex);
	return (0);
}
