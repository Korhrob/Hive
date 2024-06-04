/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:43:05 by rkorhone          #+#    #+#             */
/*   Updated: 2024/06/04 17:43:07 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_cmd
{
	char	*file;
	char	*path;
	char	**func;
}	t_cmd;

void	pipex(t_cmd *first, t_cmd *second, char **envp);
t_cmd	*prepare_cmd(char *cmd, char *file, char **envp);
void	free_char_array(char **arr);
void	free_cmd(t_cmd *cmd);
void	free_both_cmd(t_cmd *first, t_cmd *second);
void	error_handle(int ecode, int err, char *s1, t_cmd *cmd);

#endif
