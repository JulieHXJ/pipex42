/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:18:51 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/17 17:41:12 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int fd1, int fd2)
{
	int pipefd[2]; // pipefd[0] is for reading, and pipefd[1] is for writing.
	int pid;       // to record the child process status
	// check file exist
	if (!open(fd1) || !open(fd2))
	{
		return ;
	}
	pipe(pipefd); // creat pipeline between fd[0] and fd[1]
	if (pipe(pipefd) == -1)
	{
		perror("piipe");
		exit(EXIT_FAILURE);
	}
	pid = fork(); // creat child process and check
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		// child process (cmd1) goes here.
		child_process(fd1, cmd1);
		dup2(pipefd[1], 1);           // set write end of pipe to stdout,
			means cmd1 write to pipe
		close(pipefd[0]);             // close the end of pipe not used.
		execve(filename, argv, envp); // replace current process with cmd1
		exit(EXIT_SUCCESS);
	}
	else
	{
		// parent process (cmd2)
		parent_process(fd2, cmd2);
		dup2(pipefd[0], 0);           // set input of pipe to stdin,
			means read from pipe
		close(pipefd[1]);             // close writing end
		execve("path of the file", ); // cmd2
		// write to outfile
		exit(EXIT_SUCCESS);
	}
	// clean up
	clean_up(pipex);
	waitpid(pid, );
	return (EXIT_SUCCESS);
}


void	child_process(int fd, char *cmd)
{
}

void	parent_process(int fd, char *cmd)
{
}

void	execute_cmd(t_pipex *pipex, int cmd)
{
}


