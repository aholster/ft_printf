/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_char.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 14:19:45 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/18 18:30:35 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static int		ft_char_pad(const char c, t_print *const restrict clipb)
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
	if (clipb->printer(&c, 1, clipb) == -1)
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

int				ft_char(va_list args, t_print *const restrict clipb)
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
	if (clipb->printer(&c, 1, clipb) == -1)
		return (-1);
	return (1);
}
