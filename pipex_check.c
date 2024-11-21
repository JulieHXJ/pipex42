/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhuang <xhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:40:23 by xhuang            #+#    #+#             */
/*   Updated: 2024/11/17 17:40:47 by xhuang           ###   ########.fr       */
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
	if (access("infile", R_OK) == -1)
	{
		ft_printf("No permission to infile!\n");
		return (-1);
	}
	if (access("outfile", W_OK) == -1)
	{
		ft_printf("No permission to outfile!\n");
		return (-1);
	}
	// check commands format
	if (argv[1] && argv[2])
	{
		/* code */
	}
	return (0);
}