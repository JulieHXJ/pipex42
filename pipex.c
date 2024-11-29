/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:18:51 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/29 18:13:23 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipexx(t_pipex *pipex, char **envp)
{
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipex->pipefd) == -1)
		error_handling("pipe", pipex, EXIT_FAILURE);
	child1 = fork();
	if (child1 == -1)
		error_handling("fork", pipex, EXIT_FAILURE);
	child2 = fork();
	if (child2 == -1)
		error_handling("fork", pipex, EXIT_FAILURE);
	if (child1 == 0)
		child_process(pipex->infile_fd, pipex->pipefd[1], pipex->cmd1_arg,
			envp);
	else if (child2 == 0)
		child_process(pipex->pipefd[0], pipex->outfile_fd, pipex->cmd2_arg,
			envp);
	else
		parent_process(child1, child2, pipex);
}

void	child_process(int in_fd, int out_fd, char **cmd, char **envp)
{
	if (dup2(in_fd, STDIN_FILENO) == -1)
		error_handling(pipex, "dup2 stdin", EXIT_FAILURE);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		error_handling(pipex, "dup2 stdout", EXIT_FAILURE);
	close(in_fd);
	close(out_fd);
	if (execve(cmd[0], cmd, envp) == -1)
		error_handling(NULL, "dup2 stdout", EXIT_FAILURE);
	exit(EXIT_FAILURE);
}

void	parent_process(pid_t child1, pid_t child2, t_pipex *pipex)
{
	int	status;

	if (waitpid(child1, &status, 0) == -1)
	{
		perror("waitpid for child1");
		exit(EXIT_FAILURE);
	}
	if (waitpid(child2, &status, 0) == -1)
	{
		perror("waitpid for child2");
		exit(EXIT_FAILURE);
	}
	if (pipex->pipefd[0] > 0)
		close(pipex->pipefd[0]);
	if (pipex->pipefd[1] > 0)
		close(pipex->pipefd[1]);
	if (pipex->infile_fd > 0)
		close(pipex->infile_fd);
	if (pipex->outfile_fd > 0)
		close(pipex->outfile_fd);
}

void	execute_cmd(t_pipex *pipex, int cmd)
{
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	init_pipe(&pipex);
	if (check_args(argc, argv, &pipex) < 0)
	{
		return (EXIT_FAILURE);
	}
	pipex.cmd1_arg = cmd_to_array(argv[2]);
	pipex.cmd2_arg = cmd_to_array(argv[3]);
	if (!pipex.cmd1_arg || !pipex.cmd2_arg)
	{
		clean_up(&pipex);
		return (EXIT_FAILURE);
	}
	pipex.cmd1_path = make_cmd_path(pipex.cmd1_arg[0], envp);
	pipex.cmd2_path = make_cmd_path(pipex.cmd2_arg[0], envp);
	if (!pipex.cmd1_path || !pipex.cmd2_path)
	{
		clean_up(&pipex);
		return (EXIT_FAILURE);
	}
	pipexx(&pipex, envp);
	clean_up(&pipex);
	return (EXIT_SUCCESS);
}
