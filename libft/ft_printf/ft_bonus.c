/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:25:44 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/30 15:28:15 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_int(const char *s)
{
	int	num;

	num = 0;
	while (*s >= '0' && *s <= '9')
	{
		num *= 10;
		num += *s - '0';
		s++;
	}
	return (num);
}

int	ft_int_len(int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_print_space(char c, int size)
{
	int	temp;
	int	count;

	temp = 0;
	count = 0;
	while (size > 0)
	{
		temp = write(1, &c, 1);
		if (temp < 0)
			return (-1);
		count += temp;
		size--;
	}
	return (count);
}

int	ft_print_nbr_bonus(const char *s, va_list args, char prefix)
{
	int		temp;
	int		count;
	int		size;
	int		n;

	temp = 0;
	count = 0;
	n = va_arg(args, int);
	size = ft_get_int(s) - ft_int_len(n);
	while (*s >= '0' && *s <= '9')
		s++;
	if (*s != 'd')
		return (-1);
	if (prefix == '0'
		&& ft_add_or_fail(&count, ft_print_space('0', size)) < 0)
		return (-1);
	if (ft_add_or_fail(&count, ft_print_nbr(n, prefix)) < 0)
		return (-1);
	if (prefix == '-'
		&& ft_add_or_fail(&count, ft_print_space(' ', size)) < 0)
		return (-1);
	return (count);
}

int	ft_print_str_bonus(const char *s, va_list args)
{
	int		temp;
	int		count;
	int		size;
	char	*str;

	temp = 0;
	count = 0;
	size = ft_get_int(s);
	while (*s >= '0' && *s <= '9')
		s++;
	if (*s != 's')
		return (-1);
	str = va_arg(args, char *);
	while (*str != 0 && size > 0)
	{
		if (ft_add_or_fail(&count, write(1, str++, 1)) < 0)
			return (-1);
		size--;
	}
	return (count);
}
