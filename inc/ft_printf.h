/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:48:15 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/08/04 18:48:17 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"

typedef struct	s_fmt {
	char	*str;
	char	type;
	int		space;
	int		minus;
	int		plus;
	int		hash;
	char	filler;
	int		width;
	int		length;
	int		precision;
	int		z;
	int		j;
	int		null;
	int		negative;
	int		printed;
}				t_fmt;

void	get_type(int *i, const char *restrict format, t_fmt *fmt);
void	parse_format(t_fmt *fmt);

int		print_percent(t_fmt *fmt);
int		print_char(t_fmt *fmt, int c);
int		print_string(t_fmt *fmt, char *str);
int		print_signed(t_fmt *fmt, va_list args, int base);
int		print_unsigned(t_fmt *fmt, va_list args, int base);

void	apply_postfix(t_fmt *fmt);
void	ft_write(char c, t_fmt *fmt);
void	print_buf(char buf[64], t_fmt *fmt, int len);

int		ft_utoa_base(uintmax_t n, int base, char buf[64]);

#endif
