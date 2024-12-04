/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:16:33 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/30 17:20:50 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipex *pipex)
{
	pipex->infilename = NULL;
	pipex->outfilename = NULL;
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	pipex->cmd_num = 0;
	pipex->cmd1_arg = NULL;
	pipex->cmd2_arg = NULL;
	pipex->cmd1_path = NULL;
	pipex->cmd2_path = NULL;
}

int	check_args(int argc, char **argv, t_pipex *pipex, char **envp)
{
    pipex->cmd_num = argc - 2;
    
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd < 0)
		return (perror("infile"), -1);
	pipex->outfile_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile_fd < 0)
		return (perror("outfile"), -1);
	pipex->cmd1_arg = cmd_to_array(argv[2]);
	pipex->cmd2_arg = cmd_to_array(argv[3]);
	if (!pipex->cmd1_arg || !pipex->cmd2_arg)
		return (ft_printf("Invalid commands!\n"), -1);
	pipex->cmd1_path = make_cmd_path(pipex->cmd1_arg[0], envp);
	pipex->cmd2_path = make_cmd_path(pipex->cmd2_arg[0], envp);
	if (!pipex->cmd1_path || !pipex->cmd2_path)
		return (ft_printf("Command path error\n"), -1);
	return (0);
}


int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		return (ft_printf("Wrong arguments!\n"), -1);
	init_pipex(&pipex, argv, envp);
	if (check_args(argc, argv, &pipex) < 0)
	{
		error_handling(&pipex, NULL, EXIT_FAILURE);
		return (-1);
	}
	pipexx(&pipex, envp);
	clean_up(&pipex);
	return (EXIT_SUCCESS);
}