/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 21:38:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/30 10:26:35 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static int	ft_str_padding(const char *const restrict str, const size_t len,\
			t_print *const restrict clipb)
{
	int		zeroflag;
	int		padf;

	zeroflag = flagverif('0', clipb->flags);
	if (flagverif('-', clipb->flags) == -1)
	{
		if (zeroflag == 1)
			padf = ft_zero_padder(len, clipb);
		else
			padf = ft_space_padder(len, clipb);
		if (padf == -1 || clipb->printer(str, len, clipb) == -1)
			return (-1);
	}
	else
	{
		if (clipb->printer(str, len, clipb) == -1)
			return (-1);
		if (zeroflag == 1)
			padf = ft_zero_padder(len, clipb);
		else
			padf = ft_space_padder(len, clipb);
		if (padf == -1)
			return (-1);
	}
	return (1);
}

int			ft_str(va_list args, t_print *const restrict clipb)
{
	const char *restrict	str;
	size_t					len;

	str = va_arg(args, char*);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (flagverif('l', clipb->flags) == 1)
		return (-1);
	if (flagverif('.', clipb->flags) == 1)
	{
		if (len > clipb->flags->precision)
			len = clipb->flags->precision;
		else
			clipb->flags->precision = len;
	}
	if (ft_str_padding(str, len, clipb) == -1)
		return (-1);
	return (1);
}
