/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:11:31 by xhuang            #+#    #+#             */
/*   Updated: 2024/12/01 16:29:12 by xhuang           ###   ########.fr       */
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
	if (pipex->pipefd[0] > 0)
		close(pipex->pipefd[0]);
	pipex->pipefd[0] = -1;
	if (pipex->pipefd[1] > 0)
		close(pipex->pipefd[1]);
	pipex->pipefd[1] = -1;
	if (pipex->infile_fd > 0)
		close(pipex->infile_fd);
	pipex->infile_fd = -1;
	if (pipex->outfile_fd > 0)
		close(pipex->outfile_fd);
	pipex->outfile_fd = -1;
	if (pipex->cmd1_path)
		free(pipex->cmd1_path);
	pipex->cmd1_path = NULL;
	if (pipex->cmd2_path)
		free(pipex->cmd2_path);
	pipex->cmd2_path = NULL;
	if (pipex->cmd1_arg)
		free_array(pipex->cmd1_arg);
	pipex->cmd1_arg = NULL;
	if (pipex->cmd2_arg)
		free_array(pipex->cmd2_arg);
	pipex->cmd2_arg = NULL;
}

void	error_handling(t_pipex *pipex, char *text, int exit_code)
{
	if (text)
		perror(text);
	if (pipex)
		clean_up(pipex);
	exit(exit_code);
}
