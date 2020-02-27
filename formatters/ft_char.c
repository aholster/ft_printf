/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_char.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 14:19:45 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 09:51:24 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static void	ft_char_pad(const char c,\
				t_writer *const clipb,\
				const t_flag *const flags)
{
	if (flg_verif('-', flags) == -1)
	{
		if (flg_verif('0', flags) == 1)
		{
			pad_zero(flags->padding - 1, clipb);
		}
		else
		{
			pad_spaces((flags->padding - 1), clipb);
		}
	}
	ft_write_wrap(&c, 1, clipb);
	if (flg_verif('-', flags) == 1)
	{
		if (flg_verif('0', flags) == 1)
		{
			pad_zero(flags->padding - 1, clipb);
		}
		else
		{
			pad_spaces((flags->padding - 1), clipb);
		}
	}
}

int			ft_char(va_list args, t_writer *const clipb)
{
	const t_flag *const	flags = clipb->flags;
	char				c;

	c = (char)va_arg(args, int);
	if (flags->padding > 1)
	{
		ft_char_pad(c, clipb, flags);
	}
	else
	{
		ft_write_wrap(&c, 1, clipb);
	}
	return (0);
}
