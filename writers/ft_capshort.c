/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_capshort.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/21 13:13:51 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/06 14:35:55 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				ft_capshort_noprec(unsigned char *buffer, int neg, \
					unsigned short nb_len, t_print *clipb)
{
	int minus;

	minus = flagverif('-', clipb->flags);
	if (minus == -1 && flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (ft_prefix(neg, clipb) == -1)
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

static int				ft_capshort_prec(unsigned char *buffer, int neg, \
					unsigned short nb_len, t_print *clipb)
{
	int minus;

	minus = flagverif('-', clipb->flags);
	if (minus == -1 && clipb->flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (ft_prefix(neg, clipb) == -1)
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
	num_len = ft_ull_len(nb, 10);
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

int						ft_capshort(va_list args, t_print *clipb)
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
	if (nb == 0 && precision == 1 && clipb->flags->padding == 0)
		return (1);
	if (nb == 0 && precision == 1 && clipb->flags->precision < nb_len)
		ft_strcpy((char*)buffer, " ");
	if (clipb->flags->padding != 0 && (neg == -1 || \
	flagverif('+', clipb->flags) == 1 || flagverif(' ', clipb->flags) == 1))
		clipb->flags->padding -= 1;
	if (precision == 1)
		return (ft_capshort_prec(buffer, neg, nb_len, clipb));
	if (precision == -1)
		return (ft_capshort_noprec(buffer, neg, nb_len, clipb));
	return (1);
}
