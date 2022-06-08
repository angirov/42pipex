/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:00:36 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/08 13:40:49 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

void	ft_make_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	ft_check_input(argc); /////////////////////////////////////
	pipex->cmd_num = argc - 3;
	pipex->pipe_num = pipex->cmd_num - 1;
	pipex->fd1 = open(argv[1], O_RDONLY);
	pipex->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY, 0777);
	ft_make_paths(envp, pipex);
	ft_make_pipes(pipex);
	ft_make_newarvs(argv, pipex);
}

int	ft_check_input(int argc)
{
	if (argc >= 5)
		return (0);
	perror(strerror(errno)); ////////////////////////////////////////////////
	exit(1);
}

/*	This function finds the line starting with "PATH".
	Then it passes the pointer to the ponter to the first
	value path variable (after "PATH=" i.e. + 5 */

void		ft_make_paths(char **envp, t_pipex *pipex)
{
	while(ft_strncmp("PATH", *envp, 4))
		envp++;
	pipex->paths = ft_split_nullterm(*envp + 5, ':');
}

void	ft_make_pipes(t_pipex *pipex)
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

void	ft_make_newarvs(char **argv, t_pipex *pipex)
{
	int	i;

	pipex->newargvs = malloc(sizeof(char **) * pipex->cmd_num);
	i = 0;
	while (i < pipex->cmd_num)
	{
		pipex->newargvs[i] = ft_split_nullterm(argv[i + 2], ' ');
		i++;
	}
}

// char	**ft_make_newargv(char *arg_string)
// {
// 	int		newargc;
// 	char	*newstring;
// 	char	**newargv;

// 	newargc = ft_toknum(arg_string, ' ');
// 	newstring = ft_strjoin(arg_string, " NULL");
// 	newargv = ft_split(newstring, ' ');
// 	free(newstring);
// 	free(newargv[newargc]);
// 	newargv[newargc] = NULL;
// 	return (newargv);
// }

