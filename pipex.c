/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:18:51 by xhuang            #+#    #+#             */
/*   Updated: 2024/12/06 17:35:18 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_process(t_pipex *pipex, char **envp)
{
	if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
		error_handling(NULL, "dup2 stdin failed", EXIT_FAILURE);
	if (dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
		error_handling(NULL, "dup2 stdout failed", EXIT_FAILURE);
	close(pipex->pipefd[0]);
	if (execve(pipex->cmd1_path, pipex->cmd1_arg, envp) == -1)
	{
		close(pipex->infile_fd);
		close(pipex->pipefd[1]);
		free(pipex->cmd1_path);
		error_handling(NULL, "execve failed", EXIT_FAILURE);
	}
	free(pipex->cmd1_path);
	exit(EXIT_SUCCESS);
}

void	child2_process(t_pipex *pipex, char **envp)
{
	if (dup2(pipex->pipefd[0], STDIN_FILENO) == -1)
		error_handling(NULL, "dup2 stdin failed", EXIT_FAILURE);
	if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
		error_handling(NULL, "dup2 stdout failed", EXIT_FAILURE);
	close(pipex->pipefd[1]);
	if (execve(pipex->cmd2_path, pipex->cmd2_arg, envp) == -1)
	{
		close(pipex->pipefd[0]);
		close(pipex->outfile_fd);
		free(pipex->cmd2_path);
		error_handling(NULL, "execve failed", EXIT_FAILURE);
	}
	free(pipex->cmd2_path);
	exit(EXIT_SUCCESS);
}

/*
check if the child process exit normally
*/
void	parent_process(pid_t child1, pid_t child2, t_pipex *pipex)
{
	int	status;

	status = 0;
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	if (waitpid(child1, &status, 0) == -1)
		error_handling(pipex, "waitpid for child1", EXIT_FAILURE);
	if (waitpid(child2, &status, 0) == -1)
		error_handling(pipex, "waitpid for child2", EXIT_FAILURE);
}

void	pipexx(t_pipex *pipex, char **envp)
{
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipex->pipefd) == -1)
		return (error_handling(pipex, "pipe", EXIT_FAILURE));
	child1 = fork();
	if (child1 == -1)
		error_handling(pipex, "fork", EXIT_FAILURE);
	if (child1 == 0)
	{
		child1_process(pipex, envp);
	}
	child2 = fork();
	if (child2 == -1)
		error_handling(pipex, "fork", EXIT_FAILURE);
	if (child2 == 0)
	{
		child2_process(pipex, envp);
	}
	parent_process(child1, child2, pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (ft_printf("Wrong arguments!\n"), -1);
	init_pipex(&pipex);
	if (check_args(argv, &pipex, envp) < 0)
		error_handling(&pipex, NULL, EXIT_FAILURE);
	pipexx(&pipex, envp);
	clean_up(&pipex);
	return (EXIT_SUCCESS);
}
