/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 21:38:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/13 18:20:57 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				ft_str_padding(const char *restrict str, \
					unsigned short len, t_print *clipb)
{
	int minus;

	minus = flagverif('-', clipb->flags);
	if (minus == -1 && flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(len, clipb) == -1)
			return (-1);
	if (minus == -1 && flagverif('0', clipb->flags) == 1)
		if (ft_zero_padder(len, clipb) == -1)
			return (-1);
	if (clipb->printer(str, len, clipb) == -1)
		return (-1);
	if (minus == 1 && flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(len, clipb) == -1)
			return (-1);
	if (minus == 1 && flagverif('0', clipb->flags) == 1)
		if (ft_zero_padder(len, clipb) == -1)
			return (-1);
	return (1);
}

static unsigned short	ft_str_prec(unsigned short len, t_print *clipb)
{
	if (len > clipb->flags->precision)
		len = clipb->flags->precision;
	if (len < clipb->flags->precision)
		clipb->flags->precision = len;
	return (len);
}

int						ft_str(va_list args, t_print *clipb)
{
	const char *restrict	str;
	unsigned short			len;

	str = va_arg(args, char*);
	if (str == NULL)
		str = ft_strdup("(null)");
	len = ft_strlen(str);
	if (flagverif('.', clipb->flags) == 1)
		len = ft_str_prec(len, clipb);
	if (ft_str_padding(str, len, clipb) == -1)
		return (-1);
	return (1);
}
