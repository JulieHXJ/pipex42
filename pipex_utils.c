/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:11:31 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/29 16:32:17 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	clean_up(t_pipex *pipex)
{
	// close fd
	if (pipex->pipefd[0] > 0)
		close(pipex->pipefd[0]);
	if (pipex->pipefd[1] > 0)
		close(pipex->pipefd[1]);
	// free cmd path
	if (pipex->cmd1_path)
		free(pipex->cmd1_path);
	if (pipex->cmd2_path)
		free(pipex->cmd2_path);
	// free cmd array
	if (pipex->cmd1_arg)
		free_array(pipex->cmd1_arg);
	if (pipex->cmd2_arg)
		free_array(pipex->cmd2_arg);
	// wait for child prcess
	while (wait(NULL) > 0)
	{
		/* code */
	}
}

void	error_handling(t_pipex *pipex, char *text, int exit_code)
{
	if (text)
		perror(text);
	if (pipex)
		clean_up(pipex);
	exit(exit_code);
}

