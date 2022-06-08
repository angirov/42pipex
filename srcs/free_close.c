/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:06:42 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/08 20:25:26 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

void	ft_exit(int num, t_pipex *pipex)
{
	perror(ft_itoa(num));
	ft_clean_pipex(pipex);
	exit(errno);
}

void	ft_clean_pipex(t_pipex *pipex)
{
	ft_close_all_fds(pipex);
	if (pipex->paths)
		ft_free_split(pipex->paths);
	ft_free_pipes(pipex);
	ft_free_newargvs(pipex);
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

	close(pipex->fd1);
	close(pipex->fd2);
	while (j < pipex->pipe_num && pipex->pipes)
	{
		close(pipex->pipes[j][0]);
		close(pipex->pipes[j][1]);
		j++;
	}
}

/*	This function just mirrors ft_init_pipes */

void	ft_free_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->pipes)
	{
		while (i < pipex->pipe_num)
		{
			free(pipex->pipes[i]);
			i++;
		}
		free(pipex->pipes);
	}
}

/*	This function just mirrors ft_init_newarvs */

void	ft_free_newargvs(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->newargvs)
	{
		while (i < pipex->cmd_num)
		{
			ft_free_split(pipex->newargvs[i]);
			i++;
		}
		free(pipex->newargvs);
	}
}

/*	This function frees double char arrays making
	use of the fact that they were inited with
	a NULL at the end in ft_make_newargv */

// void	ft_free_split_nullterm(char **arr)
// {
// 	int i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// }

/*	Do not forget that some of double char arrays 
	may have a the last slot pointing to NULL */
// void	ft_free_split(char **arr, int n)
// {
// 	int i;

// 	i = 0;
// 	while (i++ < n)
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// }
