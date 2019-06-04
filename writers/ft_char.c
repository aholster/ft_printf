/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_char.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 14:19:45 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/03 15:06:38 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		flagverif(const unsigned char c, const t_flag *flags)
{
	unsigned short flip;

	flip = c / 64;

	if (((1LLU << (c - (flip * 64))) & flags->actiflags[flip]) > 0)
		return (1);
	return (-1);
}

static int		ft_char_pad(unsigned char c, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1)
	{
		// if (flagverif('0', clipb->flags) == 1)// do we want to impliment this?
		// {
		// 	if (pad_zero(clipb->flags->padding - 1, clipb) == -1)
		// 		return (-1);
		// }
		if (pad_spaces(clipb->flags->padding - 1, clipb) == -1)
			return (-1);
	}
	clipb->printer(&c, 1, clipb);
	if (flagverif('-', clipb->flags) == 1)
	{
		// if (flagverif('0', clipb->flags) == 1) // do we want to impliment this?
		// {
		// 	if (pad_zero(clipb->flags->padding - 1, clipb) == -1)
		// 		return (-1);
		// }
		if (pad_spaces(clipb->flags->padding - 1, clipb) == -1)
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
	if (flagverif('-', clipb->flags) == -1)
		return (ft_char_pad(c, clipb));
	if (flagverif('-', clipb->flags) == 1)
		return (ft_char_pad(c, clipb));
	clipb->printer(&c, 1, clipb);
	return (1);
}
