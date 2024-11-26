/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:11:31 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/24 18:45:07 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	clean_up(t_pipex *pipex)
{
	// close fd
	if (pipex->pipefd[0] > 0)
	{
		close(pipex->pipefd[0]);
	}
	if (pipex->pipefd[1] > 0)
	{
		close(pipex->pipefd[1]);
	}
	// free cmd path
	if (pipex->cmd1_path)
	{
		/* code */
	}
	if (pipex->cmd2_path)
	{
		/* code */
	}
	// free cmd array
	if (pipex->cmd1)
	{
		/* code */
	}
	if (pipex->cmd2)
	{
		/* code */
	}
	// wait for child prcess
	while (wait(NULL) > 0)
	{
		/* code */
	}
}

void	error_handling(t_pipex *pipex, char *text)
{
	perror(text);
	clean_up(pipex);
	exit(EXIT_FAILURE);
}

