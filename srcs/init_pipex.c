/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:00:36 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/08 11:19:19 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

void	ft_init_pipex(int argc, char **argv, t_pipex *pipex)
{
	ft_check_input(argc); /////////////////////////////////////
	pipex->fd1 = open(argv[1], O_RDONLY);
	pipex->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY, 0777);

	pipex->cmd_num = argc - 3;
	pipex->pipe_num = pipex->cmd_num - 1;

	ft_init_pipes(pipex);
	ft_init_newarvs(argv, pipex);
}

int	ft_check_input(int argc)
{
	if (argc >= 5)
		return (0);
	perror(strerror(errno)); ////////////////////////////////////////////////
	exit(1);
}

void	ft_init_pipes(t_pipex *pipex)
{
	int	i;
	int	pipe_res;

	pipex->pipes = malloc(sizeof(int *) * pipex->pipe_num);  ///////////////////////////////////////////////////////
	i = 0;
	while (i < pipex->pipe_num)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);  ///////////////////////////////////////////////////////
		pipe_res = pipe(pipex->pipes[i]);
		if (pipe_res == -1)
			printf("Failed to pipe %d.\n", i); ///////////////////////////////////////////////////////
		i++;
	}
}

void	ft_init_newarvs(char **argv, t_pipex *pipex)
{
	int	i;

	pipex->newargvs = malloc(sizeof(char **) * pipex->cmd_num);
	i = 0;
	while (i < pipex->cmd_num)
	{
		pipex->newargvs[i] = ft_make_newargv(argv[i + 2]);
		i++;
	}
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
