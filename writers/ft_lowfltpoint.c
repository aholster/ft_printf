/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowfltpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/09 13:45:41 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/13 17:33:06 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

static void	ft_x_handler(unsigned char *buffer)
{
	size_t index;

	index = 0;
	while (buffer[index] != '\0')
	{
		buffer[index] = buffer[index + 1];
		index++;
	}
}

static int	ft_float_padding(unsigned char *buffer, \
			int neg, t_print *clipb, size_t nb_len)
{
	nb_len--;
	if (flagverif('+', clipb->flags) == -1)
		nb_len--;
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (ft_prefix(neg, clipb) == -1)
		return (-1);
	ft_x_handler(buffer);
	if (flagverif('+', clipb->flags) == 1)
		nb_len--;
	if (flagverif('0', clipb->flags) == 1 && flagverif('-', clipb->flags) == -1)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, nb_len, clipb) == -1)
		return (-1);
	if (neg == -1)
		nb_len++;
	if (flagverif('-', clipb->flags) == 1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

int			ft_lowfltpoint(va_list args, t_print *clipb)
{
	char				*buffer;
	t_float				conversion;
	long double			nb;
	size_t				nb_len;
	int					neg;

	neg = ft_longdouble_conv(args, &nb, clipb->flags);
	conversion.ld = nb;
	nb_len = (size_t)ft_ull_len(conversion.llu, 10);
	if (flagverif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	if (ft_custom_ld_to_text(nb, \
	clipb->flags->precision, &buffer, &nb_len) == -1)
		return (-1);
	ft_rounder(conversion, buffer, clipb, nb_len);
	return (ft_float_padding((unsigned char*)buffer, neg, clipb, nb_len));
}
