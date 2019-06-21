/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowsci.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 11:15:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/21 13:07:57 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				ft_signhand(int neg, t_print *clipb)
{
	if (neg != -1)
	{
		if (flagverif('+', clipb->flags) == 1)
			if (clipb->printer((const unsigned char*)"+", 1, clipb) == -1)
				return (-1);
		else if (flagverif(' ', clipb->flags) == 1)
			if (clipb->printer((const unsigned char*)" ", 1, clipb) == -1)
				return (-1);
	}
	else if (clipb->printer((const unsigned char*)"-", 1, clipb) == -1)
		return (-1);
	return (1);
}

static int				ft_capsci_noprec(unsigned char *buffer, int neg, \
					unsigned short nb_len, t_print *clipb)
{
	int minus;

	minus = flagverif('-', clipb->flags);
	if (minus == -1 && flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (ft_signhand(neg, clipb) == -1)
		return (-1);
	if (flagverif('0', clipb->flags) == 1 && minus == -1)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (clipb->printer((const char *)"E+", 2, clipb) == -1)
		return (-1);
//	if (clipb->printer((const char *), 2, clipb) == -1) // print exponent number
//		return (-1);
	if (minus == 1 && clipb->flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_capsci_prec(unsigned char *buffer, int neg, \
					unsigned short nb_len, t_print *clipb)
{
	int minus;

	minus = flagverif('-', clipb->flags);
	if (minus == -1 && clipb->flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (ft_signhand(neg, clipb) == -1)
		return (-1);
	if (clipb->flags->precision > nb_len)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (clipb->printer((const char *)"E+", 2, clipb) == -1)
		return (-1);
//	if (clipb->printer((const char *), 2, clipb) == -1) // print exponent number
//		return (-1);
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
	if (nb == 0)
	{
		buffer[0] = '0';
		return (num_len);
	}
	while (temp_num >= 16)
	{
		buffer[cur_len] = base[(temp_num % 16)];
		temp_num /= 16;
		cur_len--;
	}
	buffer[cur_len] = base[temp_num];
	return (num_len);
}

int						ft_capsci(va_list args, t_print *clipb)
{
	unsigned char		buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;
	int					neg;
	int					precision;

	precision = flagverif('.', clipb->flags);
	neg = 1;
	if (ft_signconv(args, &nb, clipb->flags) == -1)
		neg = -1;
	nb_len = ft_int_len(buffer, nb);
	if (clipb->flags->padding != 0 && (neg == -1 || \
	flagverif('+', clipb->flags) == 1 || flagverif(' ', clipb->flags) == 1))
		clipb->flags->padding -= 1;
	if (precision == 1)
		return (ft_capsci_prec(buffer, neg, nb_len, clipb));
	if (precision == -1)
		return (ft_capsci_noprec(buffer, neg, nb_len, clipb));
	return (1);
}
