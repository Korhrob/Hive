/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:41:03 by rkorhone          #+#    #+#             */
/*   Updated: 2024/06/04 17:41:04 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

// redirects input to stdin and output to stdout
// NOTE: should split into two functions(?)
static int	redirect_fd(int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		close(input);
		return (-1);
	}
	close (input);
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		close(output);
		return (-1);
	}
	close(output);
	return (1);
}

// handle first child in pipe
// error handling
// file is a directory
// file exists
// read permission
// open
// redirect
// path exists
// path is a directory
// execve
static void	first_child(t_cmd *first, int pipefd[2], char **envp)
{
	int		fd;

	if (open(first->file, O_DIRECTORY) != -1)
		error_handle(1, 9, first->file, first);
	if (access(first->file, F_OK) == -1)
		error_handle(1, 6, first->file, first);
	if (access(first->file, R_OK) == -1)
		error_handle(1, 7, first->file, first);
	fd = open(first->file, O_RDONLY);
	if (fd == -1)
		error_handle(1, 6, first->file, first);
	if (redirect_fd(fd, pipefd[1]) == -1)
		error_handle(127, 2, first->file, first);
	close(pipefd[0]);
	if (access(first->path, F_OK) == -1)
		error_handle(127, 1, first->func[0], first);
	if (open(first->path, O_DIRECTORY) != -1)
		error_handle(127, 9, first->func[0], first);
	if (execve(first->path, first->func, envp) == -1)
		error_handle(127, 3, "", first);
}

// handle second child in pipe
// error handling
// file is a directory
// open, create, trucate
// write permisson
// redirect
// path exists
// path is a directory
// execve
static void	second_child(t_cmd *second, int pipefd[2], char **envp)
{
	int		fd;

	if (open(second->file, O_DIRECTORY) != -1)
		error_handle(1, 9, second->file, second);
	fd = open(second->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(second->file, W_OK) == -1)
		error_handle(1, 7, second->file, second);
	if (fd == -1)
		error_handle(1, 6, second->file, second);
	if (redirect_fd(pipefd[0], fd) == 0)
		error_handle(127, 2, second->file, second);
	close(pipefd[1]);
	if (access(second->path, F_OK) == -1)
		error_handle(127, 1, second->func[0], second);
	if (open(second->path, O_DIRECTORY) != -1)
		error_handle(127, 9, second->func[0], second);
	if (execve(second->path, second->func, envp) == -1)
		error_handle(127, 3, "", second);
}

// close pipe and wait children
static void	end_pipe(int pipefd[2], t_cmd *first, t_cmd *second)
{
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	free_both_cmd(first, second);
}

void	pipex(t_cmd *first, t_cmd *second, char **envp)
{
	int		pipefd[2];
	pid_t	cpid;

	if (pipe(pipefd) == -1)
	{
		free_both_cmd(first, second);
		error_handle(127, 5, "", NULL);
	}
	cpid = fork();
	if (cpid == -1)
	{
		free_both_cmd(first, second);
		error_handle(127, 4, "", NULL);
	}
	if (cpid == 0)
		first_child(first, pipefd, envp);
	cpid = fork();
	if (cpid == -1)
	{
		free_both_cmd(first, second);
		error_handle(127, 4, "", NULL);
	}
	if (cpid == 0)
		second_child(second, pipefd, envp);
	end_pipe(pipefd, first, second);
}
