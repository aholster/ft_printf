/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 21:38:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/05/31 19:20:33 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int				flagverif(const unsigned char c, const t_flag *flags)
{
	unsigned short flip;

	flip = c / 64;

	if (((1LLU << (c - (flip * 64))) & flags->actiflags[flip]) > 0)
		return (1);
	return (-1);
}

static int				ft_str_pad(unsigned char *str, size_t len, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1)
	{
		if (pad_spaces(clipb->flags->padding - clipb->flags->precision, clipb) == -1)
			return (-1);
	}
	len = ft_strlen((const char*)str);
	clipb->printer(str, (size_t)clipb->flags->precision, clipb);
	if (flagverif('-', clipb->flags) == 1)
	{
		if (pad_spaces(clipb->flags->padding - clipb->flags->precision, clipb) == -1)
			return (-1);
	}
	return (1);
}

static int				ft_str_prec(unsigned char *str, t_print *clipb)
{
	size_t			len;

	len = ft_strlen((char const*)str);
	if (len > (size_t)clipb->flags->precision)	 				// string will not be longer that precision
		len = (size_t)clipb->flags->precision;
	if (len < (size_t)clipb->flags->precision)					// precision is invalid if shorter than str
		clipb->flags->precision = len;
	if (clipb->flags->padding > clipb->flags->precision) 		// padding will not be longer than string
		ft_str_pad(str, len, clipb);
	if (clipb->flags->padding < clipb->flags->precision) 	
		clipb->printer(str, len, clipb);
	return (1);
}

int					ft_str(va_list ap, t_print *clipb)
{
	unsigned char	*str;
	size_t			len;

	str = va_arg(ap, unsigned char*);
	if (str == NULL)
		str = (unsigned char*)ft_strdup("(null)");
	if (flagverif('.', clipb->flags) == 1)
		return (ft_str_prec(str, clipb));
	len = ft_strlen((char const*)str);
	if (flagverif('.', clipb->flags) == -1)    // && ((clipb->flags->padding - (unsigned int)len) > 0))
		return (ft_str_pad(str, len, clipb));
	clipb->printer(str, len, clipb);
	return (1);
}