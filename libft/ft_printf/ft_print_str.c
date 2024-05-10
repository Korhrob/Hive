/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 03:50:09 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/30 14:25:23 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(const char *str)
{
	int	i;
	int	j;

	if (str == 0)
		return (write(1, "(null)", 6));
	i = 0;
	while (*str != 0)
	{
		j = write(1, str, 1);
		if (j < 0)
			return (-1);
		i += j;
		str++;
	}
	return (i);
}
