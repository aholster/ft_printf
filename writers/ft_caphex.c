/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_caphex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 18:20:19 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/16 16:25:19 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

static int				ft_caphex_noprec(char *buffer, \
				unsigned long long nb, unsigned short nb_len, t_print *clipb)
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

static int				ft_caphex_prec(char *buffer, \
					unsigned long long nb, unsigned short nb_len, \
					t_print *clipb)
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

static unsigned short	ft_int_len(char *buffer, \
					unsigned long long nb)
{
	unsigned long long	temp_num;
	unsigned short		num_len;
	unsigned short		cur_len;
	char				*base;

	base = "0123456789ABCDEF";
	temp_num = nb;
	num_len = ft_ull_len(nb, 16);
	cur_len = num_len - 1;
	if (nb == 0)
	{
		buffer[0] = '0';
		return (num_len);
	}
	while (temp_num > 16)
	{
		buffer[cur_len] = base[(temp_num % 16)];
		temp_num /= 16;
		cur_len--;
	}
	buffer[cur_len] = base[temp_num];
	return (num_len);
}

int						ft_caphex(va_list args, t_print *clipb)
{
	char				buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;
	int					precision;

	precision = flagverif('.', clipb->flags);
	if (ft_unsignconv(args, &nb, clipb->flags) == -1)
		return (-1);
	nb_len = ft_int_len(buffer, nb);
	if (flagverif('#', clipb->flags) == 1 && nb != 0 && \
	clipb->flags->padding >= 2)
		clipb->flags->padding -= 2;
	if (nb == 0 && clipb->flags->padding == 0 && precision == 1)
		return (1);
	if (nb == 0 && clipb->flags->precision == 0 && precision == 1)
		ft_strcpy((char*)buffer, " ");
	if (precision == 1)
		return (ft_caphex_prec(buffer, nb, nb_len, clipb));
	else
		return (ft_caphex_noprec(buffer, nb, nb_len, clipb));
	return (1);
}
