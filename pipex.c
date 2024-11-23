/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:18:51 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/22 15:24:52 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int fd1, int fd2, char *cmd1, char *cmd2)
{
	int pipefd[2]; // pipefd[0] is for reading, and pipefd[1] is for writing.
	int	status;
	pid_t	child1;       // to record the child process status
	pid_t	child2;
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
	child1 = fork(); // creat child process and check
	if (child1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
		// return (perror("fork"));
	}
	if (child1 == 0)
	{
		// child process (cmd1) goes here.
		child_process(fd1, cmd1);
		exit(EXIT_SUCCESS);
	}
	child1 = fork();
	if (child2 == -1)
	{
		// return (perror("fork"));
	}
	if (child2 == 0)
	{
		child_process(fd2, cmd2);
	}
	
	
	else
	{
		// parent process (cmd2)
		parent_process(fd2, cmd2);
		
	}
	// clean up
	close(pipefd[0]);
	close(pipefd[1]);             // close writing end

	clean_up(pipex);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	return (EXIT_SUCCESS);
}


void	child_process(int fd1, char *cmd1)
{
	
	dup2(pipefd[1], 1);           // set write end of pipe to stdout, means cmd1 write to pipe
	close(pipefd[0]);             // close the end of pipe not used.
	close(fd1),
	// execve(filename, argv, envp); // replace current process with cmd1
	exit()
}

void	parent_process(int fd2, char *cmd2)
{
	int status;
	waitpid(-1, &status, 0);
	dup2();
	dup2(pipefd[0], 0);        // set input of pipe to stdin, means read from pipe
	close(pipefd[1]);
	close(fd2);
	//execve("path of the file", ); 
	exit(EXIT_SUCCESS);
	
	
}

void	execute_cmd(t_pipex *pipex, int cmd)
{
}


