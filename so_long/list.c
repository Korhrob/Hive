/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:47:25 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:29 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "list.h"
#include <stdlib.h>

// creates a new list element
static t_list	*new_element(void *data)
{
	t_list	*element;

	element = malloc(sizeof(data));
	if (element == NULL)
		return (NULL);
	element->data = data;
	element->next = 0;
	return (element);
}

// creates a new list
t_list	**list_create(void)
{
	t_list	**list;

	list = malloc(sizeof(t_list **));
	if (list == NULL)
		return (NULL);
	*list = NULL;
	return (list);
}

// mode 0 only cleans list and its nodes
// mode 1 also cleans list node data
void	list_delete(t_list **list, int mode)
{
	t_list	*cur;
	t_list	*next;

	if (list == NULL)
		return ;
	cur = *list;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->data != NULL && mode == 1)
			free(cur->data);
		free(cur);
		cur = next;
	}
	free(list);
}

// creates a new list node using data
// and then adds it to the list
int	list_add(t_list **list, void *data)
{
	t_list	*cur;
	t_list	*element;

	if (list == NULL)
		return (0);
	if (data == NULL)
		return (0);
	element = new_element(data);
	if (*list == NULL)
	{
		*list = element;
		return (1);
	}
	cur = *list;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = element;
	return (1);
}

// finds specific data from list
int	list_find(t_list **list, void *data)
{
	t_list	*cur;

	if (list == 0 || *list == 0)
		return (0);
	cur = *list;
	while (cur != NULL)
	{
		if (cur->data == data)
			return (1);
		cur = cur->next;
	}
	return (0);
}
