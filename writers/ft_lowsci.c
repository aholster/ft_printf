/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowsci.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 11:15:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/16 15:59:32 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
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

static int				ft_printnum(int neg, t_print *clipb, \
							char *buffer, unsigned int nb_len)
{
	if (ft_prefix(neg, clipb) == -1)
		return (-1);
	if (flagverif('0', clipb->flags) == 1 && flagverif('-', clipb->flags) == -1)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, 1, clipb) == -1)
		return (-1);
	if (clipb->printer(&buffer[1], clipb->flags->precision, clipb) == -1)
		return (-1);
	return (1);
}

static int				ft_lowsci_neg(char *buffer, int neg, \
					size_t nb_len, t_print *clipb)
{
	const char	*num;

	num = ft_itoa(nb_len - 1);
	// if (nb_len - 1 < 10)
	// 	nb_len++;
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (ft_printnum(neg, clipb, buffer, nb_len) == -1)
		return (-1);
	if (clipb->printer("e-", 2, clipb) == -1)
		return (-1);
	if (nb_len - 1 < 10)
		if (clipb->printer("0", 1, clipb) == -1)
			return (-1);
	if (clipb->printer(num, \
	ft_strlen(num), clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_lowsci_pos(char *buffer, int neg, \
					size_t nb_len, t_print *clipb)
{
	nb_len--;
	// nb_len = clipb->flags->precision + 4 + ft_strlen((const char *)num);
	// if (nb_len - 1 < 10)
	// 	nb_len++;
	if (flagverif('+', clipb->flags) == -1)
		nb_len--;
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	// ft_x_handler(buffer);
	if (flagverif('+', clipb->flags) == 1)
		nb_len--;
	if (ft_printnum(neg, clipb, buffer, nb_len) == -1)
		return (-1);
	if (clipb->printer("e+", 2, clipb) == -1)
		return (-1);
	if (nb_len - 1 < 10)
		if (clipb->printer("0", 1, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, nb_len, clipb) == -1) // don't want to print this buffer just need something for now to print
		return (-1);
	if (neg == -1)
		nb_len++;
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_isinfnan(long double f, t_print *clipb)
{
	long l;

	l = *((long double *)&f);
	if (f != f)
	{
		if (clipb->printer("nan", 3, clipb) == -1)
			return (-1);
		return (1);
	}
	if (l == 0x7F800000)
	{
		if (clipb->printer("inf", 3, clipb) == -1)
			return (-1);
		return (1);
	}
	if (l == 0xFF800000)
	{
		if (clipb->printer("-inf", 4, clipb) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int						ft_lowsci(va_list args, t_print *clipb)
{
	char				*buffer;
	t_float				conversion;
	long double			nb;
	size_t				nb_len;
	int					neg;
	unsigned long long	expon;

	neg = ft_longdouble_conv(args, &nb, clipb->flags);
	if (ft_isinfnan(nb, clipb) == -1)
		return (-1);
		// need to move decimal point
	conversion.ld = nb;
	nb_len = (size_t)ft_ull_len(conversion.llu, 10);
	if (flagverif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	if (ft_custom_ld_to_text(nb, \
	clipb->flags->precision, &buffer, &nb_len) == -1)
		return (-1);
	ft_rounder(conversion, buffer, clipb, nb_len);
	ft_x_handler((unsigned char*)buffer);

	/* 
	nb_len = ft_int_len(buffer, nb, clipb);
	if (clipb->flags->padding != 0 && (neg == -1 || \
	flagverif('+', clipb->flags) == 1 || flagverif(' ', clipb->flags) == 1))
		clipb->flags->padding -= 1;*/
	if (nb >= 0)
		return (ft_lowsci_pos((unsigned char*)buffer, neg, nb_len, clipb));
	if (nb < 0)
		return (ft_lowsci_neg((unsigned char*)buffer, neg, nb_len, clipb));
	return (1);
}
