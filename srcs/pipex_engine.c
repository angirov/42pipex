/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:02:24 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/23 11:39:43 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

void	ft_pipex(t_pipex *pipex)
{
	int		pid;
	int		cmd_i;

	ft_make_pipex(pipex);
	cmd_i = 0;
	while (cmd_i < pipex->cmd_num)
	{
		pid = fork();
		if (pid == -1)
			ft_exit(400 + 1, pipex);
		if (pid == 0)
			ft_child(cmd_i, pipex);
		cmd_i++;
	}
	wait(NULL);
	ft_clean_pipex(pipex);
}

/*	This function finds the line starting with "PATH".
	Then it passes the pointer to the ponter to the first
	value path variable (after "PATH=" i.e. + 5 */

void	ft_make_pipex(t_pipex *pipex)
{
	pipex->fd1 = open(pipex->infile_name, O_RDONLY);
	if (pipex->fd1 < 0)
		ft_exit(100 + 1, pipex);
	pipex->fd2 = open(pipex->outfile_name, O_CREAT | O_WRONLY, 0777);
	if (pipex->fd2 < 0)
		ft_exit(100 + 2, pipex);
	ft_make_paths(pipex);
	ft_make_pipes(pipex);
}


void	ft_make_pipes(t_pipex *pipex)
{
	int	i;
	int	pipe_res;

	pipex->pipes = malloc(sizeof(int *) * pipex->pipe_num);
	i = 0;
	while (i < pipex->pipe_num)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		pipe_res = pipe(pipex->pipes[i]);
		if (pipe_res == -1)
			ft_exit(200 + i, pipex);
		i++;
	}
}

int	ft_find_path(int cmd_i, t_pipex *pipex)
{
	int		j;
	char	*path;
	char	*fpath;

	j = 0;
	while (pipex->paths[j])
	{
		path = ft_strjoin(pipex->paths[j], "/");
		fpath = ft_strjoin(path, pipex->newargvs[cmd_i][0]);
		free(path);
		if (access(fpath, 0) == 0)
		{
			free(pipex->newargvs[cmd_i][0]);
			pipex->newargvs[cmd_i][0] = fpath;
			return (1);
		}
		else
			free(fpath);
		j++;
	}
	return (0);
}
