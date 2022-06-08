/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:55:47 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/08 12:27:10 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdio.h> ////////////////////////////////////////////////////////////////////////////////////////

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

typedef	struct s_pipex
{
	int		cmd_num;
	int		pipe_num;
	int		fd1;
	int		fd2;
	int		**pipes;
	char	***newargvs;
}	t_pipex;

/* free_close.c */
void	ft_clean_pipex(t_pipex *pipex);
void	ft_close_all_fds(t_pipex *pipex);
void ft_free_pipes(t_pipex *pipex);
void	ft_free_newargvs(t_pipex *pipex);
void	ft_free_newargv(char **arr);

/* init_pipex.c */
int		ft_check_input(int argc);
char	**ft_make_newargv(char *arg_string);
void	ft_init_pipes(t_pipex *pipex);
void	ft_init_newarvs(char **argv, t_pipex *pipex);
void	ft_init_pipex(int argc, char **argv, t_pipex *pipex);

#endif
