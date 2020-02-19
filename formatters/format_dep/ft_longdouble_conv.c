/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_longdouble_conv.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/25 15:08:50 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/19 09:41:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

int			ft_longdouble_conv(va_list args,\
				long double *const holder,\
				const t_flag *const flags)
{
	t_floatneg	num;

	if (flg_verif('L', flags) == 1)
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
