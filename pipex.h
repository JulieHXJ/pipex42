/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:17:47 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/24 18:41:57 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
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
	int		infile_fd;
	int		outfile_fd;
	char	*infilename;
	char	*outfilename;
	t_bool	here_doc;
	t_bool	is_valid;
	int		pipefd[2];
	char	***cmd1_arg;
	char	***cmd2_arg;
	char	**cmd1_path;
	char	**cmd2_path;
	int		cmd_num;
}			t_pipex;

int			check_args(int argc, char **argv);
char		**get_path_dir(char **envp);
char		*make_cmd_path(char *cmd, char **envp);
char		**cmd_to_array(char *cmd);
void		free_array(char **arr);
void		clean_up(t_pipex *pipex);

#endif