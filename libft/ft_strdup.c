/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:35:52 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:50:18 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	register char	*out;
	size_t			i;

	out = malloc(ft_strlen(s1) + 1);
	if (out == 0)
		return (0);
	i = 0;
	while (s1[i] != 0)
	{
		out[i] = s1[i];
		i++;
	}
	out[i] = 0;
	return (out);
}
