/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hexpoint_handlers.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/06 10:44:11 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 11:59:17 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

unsigned short		ft_reversed(unsigned long long mantissa)
{
	unsigned short		len;
	unsigned long long	tempnum;

	tempnum = mantissa;
	len = 0;
	while (tempnum > 0)
	{
		tempnum >>= 4;
		len++;
	}
	return (len);
}

void				ft_prefix(int is_neg, t_writer *const clipb)
{
	t_flag *const	flags = clipb->flags;

	if (is_neg >= 0)
	{
		if (flg_verif('+', flags) == 1)
		{
			ft_write_wrap("+", 1, clipb);
		}
		else if (flg_verif(' ', flags) == 1)
		{
			ft_write_wrap(" ", 1, clipb);
		}
	}
	else if (is_neg < 0)
	{
		ft_write_wrap("-", 1, clipb);
	}
}
