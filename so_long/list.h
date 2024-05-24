/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIST_H
# define LIST_H

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

t_list	**list_create(void);
void	list_delete(t_list **list, int mode);
int		list_add(t_list **list, void *data);
int		list_find(t_list **list, void *data);

#endif