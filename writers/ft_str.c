/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 21:38:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/11 16:54:45 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
static int		ft_str_pad(unsigned char *str, size_t len, t_print *clipb)
{
	unsigned int diff;

	if (clipb->flags->padding  > len)
		diff = clipb->flags->padding - len;
	if (flagverif('-', clipb->flags) == -1)
	{
		if (flagverif('0', clipb->flags) == 1)
		{
			if (pad_zero(diff, clipb) == -1)
				return (-1);
		}
		else if (pad_spaces(diff, clipb) == -1)
			return (-1);
	}
	if (clipb->printer(str, len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1)
	{
		if (flagverif('0', clipb->flags) == 1)
		{
			if (pad_zero(diff, clipb) == -1)
				return (-1);
		}
		else if (pad_spaces(diff, clipb) == -1)
			return (-1);
	}
	return (1);
}

static int		ft_str_prec(unsigned char *str, size_t len, t_print *clipb)
{
	if (len > clipb->flags->precision)
		len = clipb->flags->precision;
	if (len < clipb->flags->precision)
		clipb->flags->precision = len;
	if (clipb->flags->padding > clipb->flags->precision)
		return (ft_str_pad(str, len, clipb));
	if (clipb->printer(str, len, clipb) == -1)
			return (-1);
	return (1);
}

int				ft_str(va_list ap, t_print *clipb)
{
	unsigned char	*str;
	size_t			len;

	str = va_arg(ap, unsigned char*);
	if (str == NULL)
		str = (unsigned char*)ft_strdup("(null)");
	len = ft_strlen((char const*)str);
	if (flagverif('.', clipb->flags) == 1)
		return (ft_str_prec(str, len, clipb));
	if (flagverif('.', clipb->flags) == -1 && clipb->flags->padding > len)
		return (ft_str_pad(str, len, clipb));
	if (clipb->printer(str, len, clipb) == -1)
		return (-1);
	return (1);
}
