/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:00:36 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/08 19:19:25 by vangirov         ###   ########.fr       */
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
	if (argc < 5)
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

/*	This function finds the line starting with "PATH".
	Then it passes the pointer to the ponter to the first
	value path variable (after "PATH=" i.e. + 5 */

void		ft_make_paths(char **envp, t_pipex *pipex)
{
	while(ft_strncmp("PATH", *envp, 4))
		envp++;
	pipex->paths = ft_split(*envp + 5, ':');
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
			
		i++;
	}
}

void	ft_find_cmds(t_pipex *pipex)
{
	int		i;

	i = 0;
	while (i < pipex->cmd_num)
	{
		if(!ft_find_path(i, pipex))
			ft_exit(200 + i, pipex);
		i++;
	}
}

int		ft_find_path(int cmd_i, t_pipex *pipex)
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

