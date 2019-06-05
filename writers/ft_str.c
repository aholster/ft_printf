/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 21:38:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/05 14:59:01 by jesmith       ########   odam.nl         */
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

static int		ft_str_pad(unsigned char *str, size_t len, t_print *clipb)
{
	unsigned int diff;

	diff = clipb->flags->padding - clipb->flags->precision;
	if (flagverif('-', clipb->flags) == -1)
	{
		// if (flagverif('0', clipb->flags) == 1)// do we want to impliment this?
		// {
		// 	if (pad_zero(diff, clipb) == -1)
		// 		return (-1);
		// }
		if (pad_spaces(diff, clipb) == -1)
			return (-1);
	}
	if (clipb->printer(str, len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1)
	{
		// if (flagverif('0', clipb->flags) == 1)// do we want to impliment this?
		// {
		// 	if (pad_zero(diff, clipb) == -1)
		// 		return (-1);
		// }
		if (clipb->flags->padding > (len - 1))
		{
			if (pad_spaces((clipb->flags->padding - len), clipb) == -1)
				return (-1);
		}
		else if (pad_spaces(diff, clipb) == -1)
			return (-1);
	}
	return (1);
}

static int		ft_str_prec(unsigned char *str, t_print *clipb)
{
	size_t			len;

	len = ft_strlen((char const*)str);
	if (len > (size_t)clipb->flags->precision)
		len = (size_t)clipb->flags->precision;
	if (len < (size_t)clipb->flags->precision)
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
	if (flagverif('.', clipb->flags) == 1)
		return (ft_str_prec(str, clipb));
	len = ft_strlen((char const*)str);
	if (flagverif('.', clipb->flags) == -1)
		return (ft_str_pad(str, len, clipb));
	clipb->printer(str, len, clipb);
	return (1);
}
