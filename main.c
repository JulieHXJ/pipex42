/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:25:57 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/23 15:08:20 by xhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	int fd1;
	int	fd2;
	
	init_pipe();//fill structue with default data
	check_args(argc, );//try open each file

	pipex(fd1, fd2, argv, envp);
	return(0);
	
   
}