/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_char.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 14:19:45 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/19 10:14:06 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int	ft_char_pad(const char c,\
				t_writer *const clipb,\
				const t_flag *const flags)
{
	if (flg_verif('-', flags) == -1)
	{
		if (flg_verif('0', flags) == 1)
		{
			if (pad_zero(flags->padding - 1, clipb) == -1)
				return (-1);
		}
		else if (pad_spaces((flags->padding - 1), clipb) == -1)
			return (-1);
	}
	if (clipb->self(&c, 1, clipb) == -1)
		return (-1);
	if (flg_verif('-', flags) == 1)
	{
		if (flg_verif('0', flags) == 1)
		{
			if (pad_zero(flags->padding - 1, clipb) == -1)
				return (-1);
		}
		else if (pad_spaces((flags->padding - 1), clipb) == -1)
			return (-1);
	}
	return (1);
}

int			ft_char(va_list args, t_writer *const clipb)
{
	const t_flag *const	flags = clipb->flags;
	char				c;

	c = (char)va_arg(args, int);
	if (flags->padding > 1)
	{
		if (flg_verif('-', flags) == -1)
			return (ft_char_pad(c, clipb, flags));
		else if (flg_verif('-', flags) == 1)
			return (ft_char_pad(c, clipb, flags));
	}
	else if (clipb->self(&c, 1, clipb) == -1)
		return (-1);
	return (1);
}
