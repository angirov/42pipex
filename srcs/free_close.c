/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:06:42 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/06 12:11:10 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

/* Do not forget that some of double char arrays may have a the last slot pointing to NULL */
void	ft_free_double_chararr(char **arr, int	n)
{
	int i;

	i = 0;
	while (i++ < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*	In the child process,
	this function has to be called after dup2 
	when the necessary fd's (both files and pipes)
	have been dupped to STDIN and STDOUT 
	In the parent process it has to be called
	in the overall cleanup procedure */

void	ft_close_all_fds(t_pipex *pipex)
{
	int j;
	j = 0;
	while (j < pipex->pipe_num)
	{
		close(pipex->pipes[j][0]);
		close(pipex->pipes[j][1]);
		j++;
	}
	close(pipex->fd1);
	close(pipex->fd2);
}
