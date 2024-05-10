/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 23:22:04 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/29 15:57:07 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define LOWERCASE "0123456789abcdef"
# define UPPERCASE "0123456789ABCDEF"

# include <stdarg.h>
# include <unistd.h>

int	ft_print_chr(unsigned int c);
int	ft_print_str(const char *str);
int	ft_print_nbr(int n, char prefix);
int	ft_print_nbr_u(unsigned int n);
int	ft_print_hex(unsigned long n, const char *base, char prefix);
int	ft_print_ptr(void *ptr);
int	ft_get_int(const char *s);
int	ft_int_len(int n);
int	ft_convert_arg(const char *s, va_list args, char prefix);
int	ft_printf(const char *s, ...);

int	ft_add_or_fail(int *a, int b);
int	ft_get_int(const char *s);
int	ft_int_len(int n);
int	ft_print_nbr_bonus(const char *s, va_list args, char prefix);
int	ft_print_str_bonus(const char *s, va_list args);

#endif
