#include "ft_printf.h"


static int	calculate_filler_length(t_fmt *fmt, int len)
{
	int i;

	i = fmt->width - len;
	if (fmt->negative == 1)
		i -= 1;
	else if (fmt->negative == 0 && fmt->plus == 1)
		i -= 1;
	if (fmt->precision != -1)
		i -= (fmt->precision - len);
	return (i);
}

static void	apply_prefix(t_fmt *fmt, int len)
{
	int		i;
	int		filler_length;
	
	i = 0;
	filler_length = calculate_filler_length(fmt, len);

	if (fmt->plus == 0 && fmt->negative == 0 && fmt->minus == 0 && fmt->space > 0)
		while (i < fmt->space)
		{
			ft_write(' ', fmt);
			i++;
		}
	if (fmt->filler == '0')	
	{
		if (fmt->negative == 0 && fmt->plus == 1)
			ft_write('+', fmt);
		if (fmt->negative == 1)
			ft_write('-', fmt);	
	}
	

	if (fmt->minus == 0)
		while (i < filler_length)
		{
			ft_write(fmt->filler, fmt);
			i++;
		}

	if (fmt->filler == ' ')
	{
		if (fmt->negative == 0 && fmt->plus == 1)
			ft_write('+', fmt);
		if (fmt->negative == 1)
			ft_write('-', fmt);
	}
}

long long unsigned apply_signed_cast(t_fmt *fmt, va_list args)
{
	intmax_t	number;

	if (fmt->z)
		number = va_arg(args, size_t);
	else if (fmt->j)
		number = va_arg(args, intmax_t);
	else if (fmt->length == -2)
		number = (char)va_arg(args, int);
	else if (fmt->length == -1)
		number = (short)va_arg(args, int);
	else if (fmt->length == 0)
		number = va_arg(args, int);
	else if (fmt->length == 1)
		number = va_arg(args, long);
	else
		number = va_arg(args, long long);
	if (number < 0)
	{
		fmt->negative = 1;
		return (-number);
	}
	return (number);
}

int print_signed(t_fmt *fmt, va_list args, int base)
{
	int					len;
	char				buf[64];
	long long int		number;

	number = apply_signed_cast(fmt, args);
	fmt->null = (number ? 0 : 1);
	len = ft_utoa_base(number, base, buf);
	apply_prefix(fmt, len);
	print_buf(buf, fmt, len);
	apply_postfix(fmt);
	return (fmt->printed);
}