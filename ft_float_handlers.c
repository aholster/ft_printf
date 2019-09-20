/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_float_handlers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/17 12:34:56 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/19 11:09:55 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

int				ft_float_expon_math(long double *nb)
{
	int decimal;

	decimal = 0;
	if (*nb == 0.0)
		return (decimal);
	if (*nb >= 10)
	{
		while (*nb >= 10)
		{
			*nb /= 10;
			decimal++;
		}
	}
	else if (*nb < 1)
	{
		while (*nb < 1.0)
		{
			*nb *= 10;
			decimal++;
		}
		decimal *= -1;
	}
	return (decimal);
}


void		ft_float_exceptions(char *buffer, long double nb, \
		short *expon, t_print *const clipb)
{
	if (nb == 0.0)
	{
		expon = 0;
		buffer[0] = '0';
		if (clipb->flags->precision != 0)
		{
			buffer[1] = '.';
			buffer[2] = '0';
		}
	}
}
