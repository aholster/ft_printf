/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowsci.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 11:15:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/26 11:18:17 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static int		ft_lowsci_buffer(char *buffer, t_print *const restrict clipb, \
			size_t nb_len, int expon)
{
	int					ret_val;
	int					temp;

	temp = expon;
	nb_len = clipb->flags->precision + 3;
	if (buffer[nb_len] == '.')
		nb_len--;
	ft_sci_rounder(buffer, clipb, (nb_len + 1));
	ret_val = ft_lowsci_print(buffer, nb_len, clipb, expon);
	free(buffer);
	return (ret_val);
}

int				ft_lowsci(va_list args, t_print *const clipb)
{
	char				*buffer;
	long double			nb;
	size_t				nb_len;
	int					neg;
	int					expon;

	neg = ft_longdouble_conv(args, &nb, clipb->flags);
	// if (ft_isinfnan(nb, clipb) == -1)
	// 	return (-1);
	if (flagverif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	if (ft_custom_ld_to_text(nb, \
	clipb->flags->precision, &buffer, &nb_len) == -1)
		return (-1);
	expon = ft_expon_finder(buffer, nb_len);
	if (neg == -1)
		buffer[0] = '-';
	expon += ft_expon_rounding(buffer, nb_len, clipb);
	return (ft_lowsci_buffer(buffer, clipb, nb_len, expon));
}
