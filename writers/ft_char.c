/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_char.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 14:19:45 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/11 15:03:40 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_char_pad(unsigned char c, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1)
	{
		if (flagverif('0', clipb->flags) == 1)
		{
			if (pad_zero(clipb->flags->padding - 1, clipb) == -1)
				return (-1);
		}
		else if (pad_spaces(clipb->flags->padding - 1, clipb) == -1)
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
		else if (pad_spaces(clipb->flags->padding - 1, clipb) == -1)
			return (-1);
	}
	return (1);
}

int				ft_char(va_list ap, t_print *clipb)
{
	unsigned char	c;

	c = va_arg(ap, unsigned int);
	// if (c == NULL)
	// 	c = (unsigned char*)ft_strdup("^@");
	if (clipb->flags->padding > 0)
		return (ft_char_pad(c, clipb));
	if (clipb->printer(&c, 1, clipb) == -1)
		return (-1);
	return (1);
}
