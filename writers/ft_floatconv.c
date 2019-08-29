/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_floatconv.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/25 15:08:50 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/26 12:11:24 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	va_short(va_list args, long double *holder)
{
	double	num;

	num = (double)va_arg(args, double);
	if (num >= 0)
	{
		*holder = (long double)num;
		return (1);
	}
	*holder = (long double)(-num);
	return (-1);
}

static int	va_char(va_list args, long double *holder)
{
	double	num;

	num = (double)va_arg(args, double);
	if (num >= 0)
	{
		*holder = (long double)num;
		return (1);
	}
	*holder = (long double)(-num);
	return (-1);
}

static int	va_long(va_list args, long double *holder)
{
	long	num;

	num = (long)va_arg(args, long);
	if (num >= 0)
	{
		*holder = (long double)num;
		return (1);
	}
	*holder = (long double)(-num);
	return (-1);
}

static int	va_double(va_list args, long double *holder)
{
	double	num;

	num = va_arg(args, double);
	if (num >= 0)
	{
		*holder = (long double)num;
		return (1);
	}
	*holder = (long double)(-num);
	return (-1);
}

int			ft_floatconv(va_list args, long double *holder, \
						const t_flag *flags)
{
	long double	num;

	if (flagverif('h', flags) == 1)
		return (va_short(args, holder));
	else if (doubleverif('h', flags) == 1)
		return (va_char(args, holder));
	else if (flagverif('l', flags) == 1)
		return (va_long(args, holder));
	if (doubleverif('l', flags) == 1 || flagverif('L', flags) == 1)
	{
		num = va_arg(args, long double);
		if (num >= 0)
		{
			*holder = num;
			return (1);
		}
		*holder = (-num);
		return (-1);
	}
	else
		return (va_double(args, holder));
}