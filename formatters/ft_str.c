/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 21:38:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/02 18:27:39 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int	ft_str_padding(const char *const restrict str, const size_t len,\
		t_writer *const restrict clipb)
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
		if (padf == -1 || clipb->self(str, len, clipb) == -1)
			return (-1);
	}
	else
	{
		if (clipb->self(str, len, clipb) == -1)
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

int			ft_str(va_list args, t_writer *const restrict clipb)
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
