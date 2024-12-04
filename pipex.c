/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:18:51 by xhuang            #+#    #+#             */
/*   Updated: 2024/12/04 20:02:20 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int in_fd, int out_fd, int unused_pipe, char *path, char **ag, char **envp)
{
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		error_handling(NULL, "dup2 stdin failed", EXIT_FAILURE);
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		error_handling(NULL, "dup2 stdout failed", EXIT_FAILURE);
	}
	close(unused_pipe);
	if (execve(path, ag, envp) == -1)
	{
		close(in_fd);
		close(out_fd);
		free(path);
		error_handling(NULL, "execve failed", EXIT_FAILURE);
	}
	free(path);
	exit(EXIT_SUCCESS);
}

/*
check if the child process exit normally
*/
void	parent_process(pid_t child1, pid_t child2, t_pipex *pipex)
{
	int	status;

	if (waitpid(child1, &status, 0) == -1)
		error_handling(pipex, "waitpid for child1", EXIT_FAILURE);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		error_handling(pipex, "Child process 1 failed", EXIT_FAILURE);
	if (waitpid(child2, &status, 0) == -1)
		error_handling(pipex, "waitpid for child2", EXIT_FAILURE);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		error_handling(pipex, "Child process 2 failed", EXIT_FAILURE);
}

void	pipexx(t_pipex *pipex, char **envp)
{
	pid_t	child1;
	pid_t	child2;
	int status;

	status = 0;
	if (pipe(pipex->pipefd) == -1)
		return (error_handling(pipex, "pipe", EXIT_FAILURE));
	child1 = fork();
	if (child1 == -1)
		error_handling(pipex, "fork", EXIT_FAILURE);
	if (child1 == 0)
	{
		child_process(pipex->infile_fd, pipex->pipefd[1], pipex->pipefd[0], pipex->cmd1_path,
			pipex->cmd1_arg, envp);
	}
	child2 = fork();
	if (child2 == -1)
		error_handling(pipex, "fork", EXIT_FAILURE);
	if (child2 == 0)
	{
		child_process(pipex->pipefd[0], pipex->outfile_fd, pipex->pipefd[1], pipex->cmd2_path,
			pipex->cmd2_arg, envp);
	}
	// else
	// 	parent_process(child1, child2, pipex);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	
	
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
