/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:17:47 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/30 17:25:00 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>  //access
# include <stdio.h>  // for perror
# include <stdlib.h> //malloc, free, exit
# include <string.h> //for strerror
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
	int		pipefd[2];
	char	**cmd1_arg;
	char	**cmd2_arg;
	char	*cmd1_path;
	char	*cmd2_path;
	int		cmd_num;
	t_bool	here_doc;
	t_bool	is_valid;
}			t_pipex;

void		init_pipex(t_pipex *pipex);
int			check_args(char **argv, t_pipex *pipex, char **envp);
char		**get_path_dir(char **envp);
char		**cmd_to_array(char *cmd);
char		*make_cmd_path(char *cmd, char **envp);
void		free_array(char **arr);
void		clean_up(t_pipex *pipex);
void		error_handling(t_pipex *pipex, char *text, int exit_code);
void		pipexx(t_pipex *pipex, char **envp);

#endif