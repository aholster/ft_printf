/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_decimal.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 12:06:16 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/07 16:31:10 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
static int				ft_decimal_pad(unsigned short nb_len, \
							t_print *clipb)
{
	int diff;

	diff = clipb->flags->padding - clipb->flags->precision;
	if (clipb->flags->padding < 1 && clipb->flags->precision < 1)
		return (1);
	if (flagverif('.', clipb->flags) == -1 && \
		clipb->flags->padding > clipb->flags->precision)
	{
		if (pad_spaces((diff - nb_len), clipb) == -1)
			return (-1);
	}
	else if (clipb->flags->precision < nb_len && \
	clipb->flags->padding > clipb->flags->precision)
	{
		if (pad_spaces(clipb->flags->padding - nb_len, clipb) == -1)
			return (-1);
	}
	else if (clipb->flags->padding > clipb->flags->precision)
	{
		if (pad_spaces(diff, clipb) == -1)
			return (-1);
	}
	return (1);
}

static int				ft_decimal_noprec(unsigned char *buffer, int neg, \
						unsigned short nb_len, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1 && flagverif('0', clipb->flags) == -1 \
	&& clipb->flags->padding > 0)
	{
		// printf("here\n");
		// printf("%u\n", clipb->flags->padding);
		// printf("%u\n", clipb->flags->precision);
		// getchar();
		if (ft_decimal_pad(nb_len, clipb) == -1)
			return (-1);
	}
	if (neg == -1)
	{
		if (clipb->printer((const unsigned char*)"-", 1, clipb) == -1)
			return (-1);
	}
	if (flagverif('0', clipb->flags) == 1)
	{
		if (pad_zero((clipb->flags->padding - clipb->flags->precision \
		- nb_len), clipb) == -1)
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

static int				ft_decimal_prec(unsigned char *buffer, int neg, \
						unsigned short nb_len, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1 /*&& clipb->flags->precision < clipb->flags->padding */&& clipb->flags->padding != 0)
	{
		// printf("here\n");
		// printf("%u\n", clipb->flags->padding);
		// printf("%u\n", clipb->flags->precision);
		// getchar();
		if (ft_decimal_pad(nb_len, clipb) == -1)
			return (-1);
	}
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
		if (ft_decimal_pad(nb_len, clipb) == -1)
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
	if (nb == 0)
	{
		buffer[0] = '0';
		return (num_len);
	}
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
	// if ((flagverif('.', clipb->flags) == -1 || clipb->flags->precision == 0) && clipb->flags->padding == 0)
	// {
	// 	// if (neg == -1)
	// 	// {
	// 	// 	if (clipb->printer((const unsigned char*)"-", 1, clipb) == -1)
	// 	// 		return (-1);
	// 	// }
	// 	if (clipb->printer((const unsigned char*)ft_itoa(nb), (size_t)nb_len, clipb) == -1)
	// 		return (-1);
	// 	return (1);
	// }
	if (neg == -1)
		clipb->flags->padding -= 1;
	if (flagverif('.', clipb->flags) == 1)
		return (ft_decimal_prec(buffer, neg, nb_len, clipb));
	if (flagverif('.', clipb->flags) == -1)
		return (ft_decimal_noprec(buffer, neg, nb_len, clipb));
	return (1);
}
