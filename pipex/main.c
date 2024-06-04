/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:41:22 by rkorhone          #+#    #+#             */
/*   Updated: 2024/06/04 17:41:24 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*first;
	t_cmd	*second;

	if (argc != 5)
		return (EXIT_FAILURE);
	first = prepare_cmd(argv[2], argv[1], envp);
	if (first == NULL)
		error_handle(EXIT_FAILURE, 8, "", NULL);
	second = prepare_cmd(argv[3], argv[4], envp);
	if (second == NULL)
		error_handle(EXIT_FAILURE, 8, "", NULL);
	pipex(first, second, envp);
	return (0);
}

// pipefd[0] for reading the pipe
// pipefd[1] for writing in the pipe

// first child
// redirect infile > stdin
// redirect pipe write < stdout
// execve from stdin (infile)

// redurects pipe read > stdin
// redirect outfile < stdout
// execve from pipe read

// with trim '' doesnt work
// in ''
// out '

// char **split;
// split = ft_split_quotes(argv[3], ' ', 1);
// for (int i = 0; split[i] != NULL; i++)
// 	ft_printf("_%s_\n", split[i]);
// return (0);
