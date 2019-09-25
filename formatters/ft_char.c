/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_char.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 14:19:45 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/18 20:24:57 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static int		ft_char_pad(const char c, t_writer *const restrict clipb)
{
	if (flagverif('-', clipb->flags) == -1)
	{
		if (flagverif('0', clipb->flags) == 1)
		{
			if (pad_zero(clipb->flags->padding - 1, clipb) == -1)
				return (-1);
		}
		else if (pad_spaces((clipb->flags->padding - 1), clipb) == -1)
			return (-1);
	}
	if (clipb->self(&c, 1, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1)
	{
		if (flagverif('0', clipb->flags) == 1)
		{
			if (pad_zero(clipb->flags->padding - 1, clipb) == -1)
				return (-1);
		}
		else if (pad_spaces((clipb->flags->padding - 1), clipb) == -1)
			return (-1);
	}
	return (1);
}

int				ft_char(va_list args, t_writer *const restrict clipb)
{
	char	c;

	c = (char)va_arg(args, int);
	if (clipb->flags->padding > 1)
	{
		if (flagverif('-', clipb->flags) == -1)
			return (ft_char_pad(c, clipb));
		if (flagverif('-', clipb->flags) == 1)
			return (ft_char_pad(c, clipb));
	}
	if (clipb->self(&c, 1, clipb) == -1)
		return (-1);
	return (1);
}