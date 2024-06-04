/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:40:54 by rkorhone          #+#    #+#             */
/*   Updated: 2024/06/04 17:40:56 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>

// free a null terminated char array and its contents
void	free_char_array(char **arr)
{
	int	index;

	if (arr == NULL)
		return ;
	index = 0;
	while (arr[index] != 0)
	{
		free(arr[index]);
		index++;
	}
	free(arr);
}

// free a cmd struct and its contents
void	free_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->func[0] != cmd->path)
		free(cmd->path);
	free_char_array(cmd->func);
	free(cmd);
}

// free both commands and their contents
void	free_both_cmd(t_cmd *first, t_cmd *second)
{
	free_cmd(first);
	free_cmd(second);
}

// prints custom error message err and exit with ecode
// s1 and s2 can be used to print parameters
void	error_handle(int ecode, int err, char *s1, t_cmd *cmd)
{
	if (s1 == NULL)
		s1 = "";
	ft_printf_fd(STDERR_FILENO, "pipex: ");
	if (err == 1)
		ft_printf_fd(STDERR_FILENO, "%s: command not found\n", s1);
	else if (err == 2)
		ft_printf_fd(STDERR_FILENO, "dup2: failed\n");
	else if (err == 3)
		ft_printf_fd(STDERR_FILENO, "execve: failed\n");
	else if (err == 4)
		ft_printf_fd(STDERR_FILENO, "fork: failed\n");
	else if (err == 5)
		ft_printf_fd(STDERR_FILENO, "pipe: failed\n");
	else if (err == 6)
		ft_printf_fd(STDERR_FILENO, "%s: No such file or directory\n", s1);
	else if (err == 7)
		ft_printf_fd(STDERR_FILENO, "%s: Permission denied\n", s1);
	else if (err == 8)
		ft_printf_fd(STDERR_FILENO, "memory allocation failed\n");
	else if (err == 9)
		ft_printf_fd(STDERR_FILENO, "%s: is a directory\n", s1);
	else if (err == 10)
		ft_printf_fd(STDERR_FILENO, "syntax error: unexpected end of file\n");
	free_cmd(cmd);
	exit (ecode);
}
