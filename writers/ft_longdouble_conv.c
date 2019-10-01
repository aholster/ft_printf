/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_longdouble_conv.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/25 15:08:50 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/01 12:17:55 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

int			ft_longdouble_conv(va_list args, long double *holder, \
						const t_flag *flags)
{
	union				u_longdouble
	{
		long double		ld;
		unsigned char	byte[10];
	}					t_longdouble;
//	t_floatneg	num;
	if (flagverif('L', flags) == 1)
	{
		t_longdouble.ld = va_arg(args, long double);
	}
	else
	{
		t_longdouble.ld = (long double)va_arg(args, double);
	}
	*holder = t_longdouble.ld;
	if ((t_longdouble.byte[9] & 0x80) != 0)
	{
		return (-1);
	}
	return (1);
}
