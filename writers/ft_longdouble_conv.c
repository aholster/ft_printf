/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_longdouble_conv.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/25 15:08:50 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/30 18:32:45 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

// typedef union		u_floatneg
// {
// 	long double		ld;
// 	unsigned char	byte[10];
// }					t_floatneg;

int			ft_longdouble_conv(va_list args, long double *holder, \
						const t_flag *flags)
{
	t_floatneg	num;

	if (flagverif('L', flags) == 1)
	{
		num.ld = va_arg(args, long double);
	}
	else
	{
		num.ld = (long double)va_arg(args, double);
	}
	*holder = num.ld;
	if ((num.byte[9] & 0x80) != 0)
	{
		return (-1);
	}
	return (1);
}
