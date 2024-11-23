/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_prep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:40:23 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/23 15:52:48 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_args(int argc, char **argv)
{
	// check arguments
	if (argc != 5)
	{
		ft_printf("Wrong arguments!\n");
		return (-1);
	}
	// check file access
	int fd1 = open(argv[1], O_RDONLY);
	int fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
	{
		return(-1);
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
	// check commands format
	if (argv[1] && argv[2])
	{
		/* code */
	}
	return (0);
}

char	*find_cmd(char *cmd, char **envp)
{
	char	*path = NULL;
	char	*full_path;
	int i;
	
	// extract path from envp
	while (*envp)
	{
		if(ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = *envp + 5;
			break;
		}
		envp++;
	}
	if (!path)
	{
		return (NULL);//if no path found end the process
	}
	
	//split path into array
	char **dir = ft_split(path, ':');
	if (!dir)
	{
		return (NULL);
	}
	
	//put strings together and make the full path 
	i = 0;
	while (dir[i])
	{
		full_path = malloc(ft_strlen(dir[i]) + ft_strlen(cmd) + 2); // directory path + / + command name + null terminator
		if (!full_path)
		{
			return (NULL);
		}
		ft_printf();//print out the full path
	}
	
	
	
}


char	**args_to_array()
{
	
}

