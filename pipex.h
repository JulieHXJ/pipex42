/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:17:47 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/23 15:01:56 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft_to_use/libft.h"
# include <fcntl.h>  //access
# include <stdio.h>  // for perror
# include <stdlib.h> //malloc, free, exit
# include <string.h> //for strerror
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h> //for open, close, read, write, dup, execve, fork, pipe, unlink

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef struct s_pipex
{
	int		infile;
	char	*infilename;
	int		outfile;
	char	*outfilename;
	int		pipefd[2];
	char	**cmd1;
	char	**cmd2;
	char	*cmd1_path;
	char	*cmd2_path;
}			t_pipex;


int	check_args(int argc, char **argv);

#endif