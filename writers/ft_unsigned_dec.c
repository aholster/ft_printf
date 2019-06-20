/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsigned_dec.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 19:12:27 by aholster       #+#    #+#                */
/*   Updated: 2019/06/20 13:53:28 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				ft_unsigned_dec_noprec(unsigned char *buffer, \
					unsigned short nb_len, t_print *clipb)
{
	int minus;

	minus = flagverif('-', clipb->flags);
	if (minus == -1 && flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (flagverif('0', clipb->flags) == 1 && minus == -1)
	{
		if ((clipb->flags->padding - clipb->flags->precision) > nb_len)
		{
			if (ft_zero_padder(nb_len, clipb) == -1)
				return (-1);
		}
	}
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (minus == 1 && clipb->flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_unsigned_dec_prec(unsigned char *buffer, \
					unsigned short nb_len, t_print *clipb)
{
	int minus;

	minus = flagverif('-', clipb->flags);
	if (minus == -1 && clipb->flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
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

static unsigned short	ft_int_len(unsigned char *buffer, \
					unsigned long long nb)
{
	unsigned long long	temp_num;
	unsigned short		num_len;
	unsigned short		cur_len;
	char				*base;

	base = "0123456789";
	temp_num = nb;
	num_len = (unsigned short)ft_nbrlen(nb, 10);
	cur_len = num_len - 1;
	while (temp_num >= 10)
	{
		buffer[cur_len] = base[(temp_num % 10)];
		temp_num /= 10;
		cur_len--;
	}
	buffer[cur_len] = base[temp_num];
	return (num_len);
}

int						ft_unsigned_dec(va_list args, t_print *clipb)
{
	unsigned char		buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;
	int					precision;

	precision = flagverif('.', clipb->flags);
	if (ft_unsignconv(args, &nb, clipb->flags) == -1)
		return (-1);
	nb_len = ft_int_len(buffer, nb);
	if (nb == 0 && clipb->flags->padding == 0 && precision == 1)
		return (1);
	if (nb == 0 && clipb->flags->precision < nb_len && precision == 1)
		ft_strcpy((char*)buffer, " ");
	if (precision == 1)
		return (ft_unsigned_dec_prec(buffer, nb_len, clipb));
	if (precision == -1)
		return (ft_unsigned_dec_noprec(buffer, nb_len, clipb));
	return (1);
}
