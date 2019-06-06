/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_decimal.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 12:06:16 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/06 18:38:42 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				ft_decimal_pad(unsigned short nb_len, int neg,\
							t_print *clipb)
{
	int diff;

	diff = clipb->flags->padding - clipb->flags->precision;
	if (neg == -1)
		diff--;
	if (clipb->flags->precision < 1)
	{
		if (clipb->flags->padding - 1 > nb_len)
		{
			if (pad_spaces((diff - nb_len), clipb) == -1)
				return (-1);
		}
	}
	else if (clipb->flags->padding > clipb->flags->precision)
	{
		if (clipb->flags->padding - 1 > nb_len)
		{
			if (pad_spaces(diff, clipb) == -1)
				return (-1);
		}
	}
	return (1);
}

static int				ft_decimal_noprec(unsigned char *buffer, int neg, \ // five parameters
						unsigned short nb_len, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1 && clipb->flags->padding > nb_len)
	{
		if (ft_decimal_pad(nb_len, neg, clipb) == -1)
			return (-1);
	}
	if (neg == -1)
	{
		if (clipb->printer((const unsigned char*)"-", 1, clipb) == -1)
			return (-1);
	}
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > nb_len)
	{
		if (neg == -1)
			nb_len++;
		if (pad_spaces(clipb->flags->padding - nb_len, clipb) == -1)
			return (-1);
	}
	return (1);
}

static int				ft_decimal_prec(unsigned char *buffer, int neg, \
						unsigned long long nb, unsigned short nb_len, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1 && clipb->flags->padding != 0)
	{
		if (ft_decimal_pad(nb_len, neg, clipb) == -1)
			return (-1);
	}
	if (nb == 0 && clipb->flags->precision == 0)
		ft_strcpy((char*)buffer, " ");
	if (neg == -1)
	{
		if (clipb->printer((const unsigned char*)"-", 1, clipb) == -1)
			return (-1);
	}
	if (clipb->flags->precision > nb_len)
	{
		if (pad_zero((clipb->flags->precision - nb_len), clipb) == -1)
			return (-1);
	}
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1)
	{
		if (ft_decimal_pad(nb_len, neg, clipb) == -1)
			return (-1);
	}
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

int						ft_decimal(va_list ap, t_print *clipb)
{
	unsigned char		buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;
	int					neg;

	neg = 1;
	if (ft_signconv(ap, &nb, clipb->flags) == -1)
		neg *= -1;
	nb_len = ft_int_len(buffer, nb);
	if (nb == 0 && clipb->flags->padding == 0 && \
	flagverif('.', clipb->flags) == 1)
		return (1);
	if (flagverif('.', clipb->flags) == 1)
		return (ft_decimal_prec(buffer, neg, nb, nb_len, clipb));
	if (flagverif('.', clipb->flags) == -1)
		return (ft_decimal_noprec(buffer, neg, nb_len, clipb));
	return (1);
}
