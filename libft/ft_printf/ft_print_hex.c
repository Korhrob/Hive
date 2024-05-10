/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 03:36:41 by rkorhone          #+#    #+#             */
/*   Updated: 2023/12/04 14:53:37 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_hex_r(unsigned long n, const char *base, int *count)
{
	int	out;

	out = 0;
	if (n >= 16)
		out = ft_print_hex_r(n / 16, base, count);
	if (out < 0)
		return (-1);
	out = write(1, &base[n % 16], 1);
	(*count)++;
	return (out);
}

int	ft_print_hex(unsigned long n, const char *base, char prefix)
{
	int	count;
	int	error;

	count = 0;
	if (prefix == '#' && n != 0)
		count = write(1, "0x", 2);
	if (count < 0)
		return (-1);
	error = ft_print_hex_r(n, base, &count);
	if (error < 0)
		return (-1);
	return (count);
}
