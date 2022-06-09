/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:55:47 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/09 20:34:15 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_pipex
{
	int		cmd_num;
	int		pipe_num;
	int		fd1;
	int		fd2;
	char	**paths;
	int		**pipes;
	char	***newargvs;
}	t_pipex;

/* free_close.c */
void	ft_exit(int num, t_pipex *pipex);
void	ft_clean_pipex(t_pipex *pipex);
void	ft_close_all_fds(t_pipex *pipex);
void	ft_free_pipes(t_pipex *pipex);
void	ft_free_newargvs(t_pipex *pipex);

/* init_pipex.c */
void	ft_make_pipex(int argc, char **argv, char **envp, t_pipex *pipex);
int		ft_check_input(int argc);
void	ft_make_paths(char **envp, t_pipex *pipex);
void	ft_make_pipes(t_pipex *pipex);
void	ft_make_newarvs(char **argv, t_pipex *pipex);
int		ft_find_path(int cmd_i, t_pipex *pipex);

/* child.h */
int		ft_set_stdin(int cmd_i, t_pipex *pipex);
int		ft_set_stdout(int cmd_i, t_pipex *pipex);
void	ft_child(int cmd_i, t_pipex *pipex);

#endif
