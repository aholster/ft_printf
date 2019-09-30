/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_caphex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 18:20:19 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/30 10:31:54 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static int				ft_caphex_noprec(char *buffer, unsigned long long nb, \
					unsigned short nb_len, t_print *const restrict clipb)
{
	int minus;

	minus = flagverif('-', clipb->flags);
	if (minus == -1 && flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (flagverif('#', clipb->flags) == 1 && nb != 0)
		if (clipb->printer("0X", 2, clipb) == -1)
			return (-1);
	if (flagverif('0', clipb->flags) == 1 && minus == -1)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, ((size_t)nb_len), clipb) == -1)
		return (-1);
	if (minus == 1 && clipb->flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_caphex_prec(char *buffer, unsigned long long nb, \
					unsigned short nb_len, t_print *const restrict clipb)
{
	int minus;

	minus = flagverif('-', clipb->flags);
	if (minus == -1 && clipb->flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (flagverif('#', clipb->flags) == 1 && nb != 0)
		if (clipb->printer("0X", 2, clipb) == -1)
			return (-1);
	if (clipb->flags->precision > nb_len)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (minus == 1 && clipb->flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static unsigned short	ull_to_hex(char *buffer, unsigned long long nb)
{
	unsigned short		index;
	char				*base;

	base = "0123456789ABCDEF";
	index = 0;
	if (nb == 0)
	{
		buffer[0] = '0';
		return (1);
	}
	while (nb > 0)
	{
		buffer[index] = base[nb & 0XFLLU];
		nb >>= 4;
		index++;
	}
	return (index);
}

int						ft_caphex(va_list args, \
					t_print *const restrict clipb)
{
	char				buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;
	int					precision;

	precision = flagverif('.', clipb->flags);
	ft_unsignconv(args, &nb, clipb->flags);
	nb_len = ull_to_hex(buffer, nb);
	if (flagverif('#', clipb->flags) == 1 && nb != 0 && \
		clipb->flags->padding >= 2)
		clipb->flags->padding -= 2;
	if (nb == 0 && precision == 1)
	{
		if (clipb->flags->padding == 0)
			return (1);
		if (clipb->flags->precision == 0)
			ft_strcpy(buffer, " ");
	}
	if (precision == 1)
		return (ft_caphex_prec(buffer, nb, nb_len, clipb));
	else
		return (ft_caphex_noprec(buffer, nb, nb_len, clipb));
	return (1);
}
