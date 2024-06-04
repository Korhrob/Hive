/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:41:11 by rkorhone          #+#    #+#             */
/*   Updated: 2024/06/04 17:41:17 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

// find 'name' in envp
// return entire line after 'name='
static char	*get_path(char **envp, const char *name)
{
	if (!envp)
		return (NULL);
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, name, 4) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

// try all paths in 'path' string
// returns null path if it doesnt exist
static char	*try_path(char **func, char *path)
{
	char	**path_arr;
	char	*out;
	char	*temp;
	int		i;

	if (!path)
		return (*func);
	path_arr = ft_split(path, ':');
	if (!path_arr)
		return (NULL);
	out = func[0];
	i = -1;
	while (path_arr[++i] != NULL)
	{
		temp = ft_strjoin_c(path_arr[i], func[0], '/');
		if (access(temp, F_OK) == 0)
		{
			out = ft_strdup(temp);
			free(temp);
			break ;
		}
		free(temp);
	}
	free_char_array(path_arr);
	return (out);
}

// parse and prepare cmd struct
// also handle if quote is not closed
t_cmd	*prepare_cmd(char *cmd, char *file, char **envp)
{
	t_cmd	*out;

	out = NULL;
	if (!cmd || !file)
		return (NULL);
	out = malloc(sizeof(t_cmd));
	if (!out)
		return (NULL);
	out->file = file;
	out->func = ft_split_quotes(cmd, ' ', 1);
	if (!out->func)
	{
		free (out);
		return (NULL);
	}
	out->path = get_path(envp, "PATH");
	out->path = try_path(out->func, out->path);
	return (out);
}
