/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_prep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:40:23 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/24 18:35:59 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_args(int argc, char **argv)
{
	int	fd1;
	int	fd2;

	// check arguments
	if (argc != 5)
	{
		ft_printf("Wrong arguments!\n");
		return (-1);
	}
	// check file access
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
	{
		return (-1);
	}
	// if (access("infile", R_OK) == -1)
	// {
	// 	ft_printf("No permission to infile!\n");
	// 	return (-1);
	// }
	// if (access("outfile", W_OK) == -1)
	// {
	// 	ft_printf("No permission to outfile!\n");
	// 	return (-1);
	// }
	// check commands
	if (argv[1] && argv[2])
	{
		return (-1);
	}
	return (0);
}

// extract path from envp and split into array
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

	arr = ft_split(cmd, ' ');
	if (!arr || !arr[0])
		return (NULL);
	return (arr);
}

/*
*takes a path and split into array and reform with cmd, then check the path by access it. 
*/
char	*make_cmd_path(char *cmd, char **envp)
{
	char	*path;
	char	*full_path;
	char	**dir;
	char	**cmd_name;
	int		i;

	i = 0;
	dir = get_path_dir(envp);
	cmd_name = cmd_to_array(cmd);
	if (!cmd_name)
		return (free_array(dir), NULL);
	while (dir[i])
	{
		full_path = malloc(ft_strlen(dir[i]) + ft_strlen(cmd_name[0]) + 2);
		if (!full_path)
			return (free_array(dir), free_array(cmd_name), NULL);
		path = ft_strjoin(dir[i], "/");
		full_path = ft_strjoin(path, cmd_name[0]);
		free(path);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_array(dir), free_array(cmd_name), full_path);
		free(full_path);
		i++;
	}
	return (free_array(dir), free_array(cmd_name), NULL);
}
