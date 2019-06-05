/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_decimal.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 12:06:16 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/05 18:43:49 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				ft_decimal_pad(unsigned short nb_len, int nb,\
							t_print *clipb)
{
	unsigned int diff;

	if (clipb->flags->padding > clipb->flags->precision)
		diff = clipb->flags->padding - clipb->flags->precision;
	else
		diff = clipb->flags->padding;
	if (clipb->flags->precision < 1)
	{
		if (diff > nb_len)
		{
			if (pad_spaces((diff - nb_len), clipb) == -1)
				return (-1);
		}
	}
	else if (clipb->flags->padding > clipb->flags->precision)
	{
		if (diff > nb_len)
		{
			if (nb < 0)
				diff -= 1;
			if (pad_spaces(diff, clipb) == -1)
				return (-1);
		}
	}
	return (1);
}

static int				ft_decimal_prec(unsigned char *buffer,\
							unsigned short nb_len, int nb, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1)
	{
		if (ft_decimal_pad(nb_len, nb, clipb) == -1)
			return (-1);
	}
	if (clipb->flags->precision > nb_len)
	{
		if (nb < 0)
		{
			if (clipb->printer((const unsigned char*)"-0", 2, clipb) == -1)
				return (-1);
		}
		if (pad_zero((clipb->flags->precision - nb_len), clipb) == -1)
			return (-1);
	}
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1)
	{
		if (ft_decimal_pad(nb_len, nb, clipb) == -1)
			return (-1);
	}
	return (1);
}

static unsigned short	ft_max_min(unsigned char *buffer, \
							unsigned short num_len, t_print *clipb)
{
	if (clipb->flags->precision < num_len)
		ft_strcpy((char*)buffer, "-2147483648");
	else
		ft_strcpy((char*)buffer, "2147483648");
	return (num_len + 1);
}

static unsigned short	ft_int_len(unsigned char *buffer, \
							int nb, t_print *clipb)
{
	int					temp_num;
	unsigned short		num_len;
	unsigned short		cur_len;
	char				*base;

	base = "0123456789";
	temp_num = nb;
	num_len = (unsigned short)ft_nbrlen(nb, 10) - 1;
	cur_len = num_len;
	if (nb == -2147483648)
		return (ft_max_min(buffer, num_len, clipb));
	if (nb < 0)
		temp_num *= -1;
	if (nb < 0 && clipb->flags->precision != 0)
		cur_len--;
	while (temp_num >= 10)
	{
		buffer[cur_len] = base[(temp_num % 10)];
		temp_num /= 10;
		cur_len--;
	}
	buffer[cur_len] = base[temp_num];
	if (nb < 0 && clipb->flags->precision < num_len)
		buffer[0] = '-';
	return (num_len + 1);
}

int						ft_decimal(va_list ap, t_print *clipb)
{
	unsigned char		buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;

	nb = (unsigned long long)va_arg(ap, unsigned long long);
	nb_len = ft_int_len(buffer, nb, clipb);
	if (flagverif('.', clipb->flags) == 1)
		return (ft_decimal_prec(buffer, nb_len, nb, clipb));
	if (flagverif('-', clipb->flags) == -1 && clipb->flags->padding > nb_len)
	{
		if (pad_spaces(clipb->flags->padding - nb_len, clipb) == -1)
			return (-1);
	}
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > nb_len)
	{
		if (pad_spaces(clipb->flags->padding - nb_len, clipb) == -1)
			return (-1);
	}
	return (1);
}
