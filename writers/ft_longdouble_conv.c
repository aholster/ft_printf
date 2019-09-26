/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_longdouble_conv.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/25 15:08:50 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/23 10:24:03 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"
#include <stdio.h>
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

int			ft_longdouble_conv(va_list args, long double *holder, \
						const t_flag *flags)
{
	long double	num;

	if (flagverif('l', flags) == 1 || doubleverif('l', flags) == 1)
		return (va_double(args, holder));
	if (flagverif('L', flags) == 1)
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