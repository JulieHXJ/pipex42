/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_prep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:40:23 by xhuang            #+#    #+#             */
/*   Updated: 2024/12/03 17:39:56 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipex *pipex)
{
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	pipex->cmd_num = 2;
	pipex->cmd1_arg = NULL;
	pipex->cmd2_arg = NULL;
	pipex->cmd1_path = NULL;
	pipex->cmd2_path = NULL;
}

int	check_args(char **argv, t_pipex *pipex, char **envp)
{
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd < 0)
		return (perror("infile"), -1);
	pipex->outfile_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile_fd < 0)
		return (perror("outfile"), -1);
	pipex->cmd1_arg = cmd_to_array(argv[2]);
	pipex->cmd2_arg = cmd_to_array(argv[3]);
	if (!pipex->cmd1_arg || !pipex->cmd2_arg)
		error_handling(pipex, "Invalid commands", EXIT_FAILURE);
	pipex->cmd1_path = make_cmd_path(pipex->cmd1_arg[0], envp);
	pipex->cmd2_path = make_cmd_path(pipex->cmd2_arg[0], envp);
	if (!pipex->cmd1_path || !pipex->cmd2_path)
		error_handling(pipex, "Command path error", EXIT_FAILURE);
	return (0);
}

/*
 * extract path from envp and split into array for using
 */
char	**get_path_dir(char **envp)
{
	char	*temp;
	char	**dir;

	temp = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			temp = *envp + 5;
			break ;
		}
		envp++;
	}
	if (!temp)
		return (NULL);
	dir = ft_split(temp, ':');
	if (!dir)
		return (NULL);
	return (dir);
}

/*
 * take one cmd argument change into 2D array
 */
char	**cmd_to_array(char *cmd)
{
	char	**arr;

	if (!cmd || ft_strlen(cmd) == 0)
		return (NULL);
	arr = ft_split(cmd, ' ');
	if (!arr || !arr[0])
		return (NULL);
	return (arr);
}

/*
 * take path from array and reform with cmd
 * and check accessability
 */
char	*make_cmd_path(char *cmd, char **envp)
{
	char	*path;
	char	*full_path;
	char	**dir;
	char	**cmd_name;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
        return (ft_strdup(cmd));
	dir = get_path_dir(envp);
	cmd_name = cmd_to_array(cmd);
	if (!dir || !cmd_name)
		return (free_array(dir), free_array(cmd_name), NULL);
	i = 0;
	while (dir[i])
	{
		path = ft_strjoin(dir[i], "/");
		if (!path)
			return (free_array(dir), free_array(cmd_name), NULL);
		full_path = ft_strjoin(path, cmd_name[0]);
		free(path);
		if (!full_path)
			return (free_array(dir), free_array(cmd_name), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_array(dir), free_array(cmd_name), full_path);
		free(full_path);
		full_path = NULL;
		i++;
	}
	return (free_array(dir), free_array(cmd_name), NULL);
}
