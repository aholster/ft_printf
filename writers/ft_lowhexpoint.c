/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowhexpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/28 14:42:40 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/06 19:24:36 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int				exponentbuffer(t_print *clipb, short expon)
{
	unsigned char	buffer[8];
	size_t			index;
	int				neg;

	neg = expon;
	index = (size_t)ft_nbrlen((long long)expon, 10);
	if (expon == 0 || index == 1)
		index++;
	if (expon < 0)
		expon *= -1;
	while (index > 1)
	{
		buffer[index] = (expon % 10) + '0';
		index--;
		expon /= 10;
	}
	if (neg < 0)
		buffer[1] = '-';
	else
		buffer[1] = '+';
	buffer[0] = 'p';
	if (clipb->printer(buffer, index + 2, clipb) == -1)
		return (-1);
	return (1);
}

static unsigned short		ft_lowshrthd_prec(unsigned char *buffer, \
						t_print *clipb)
{
	size_t			dec_len;
	unsigned short	index;

	index = 0;
	dec_len = 0;
	while (buffer[index] != '\0')
	{
		if (buffer[index] == '.')
			dec_len = index;
		index++;
	}
	if (flagverif(' ', clipb->flags) == 1)
		index++;
	dec_len = index - dec_len;
	if (flagverif('.', clipb->flags) == 1)
		if (dec_len > clipb->flags->precision && dec_len < index)
			index = (index + 1) - dec_len + clipb->flags->precision;
	if (dec_len < clipb->flags->precision)
		clipb->flags->precision -= (dec_len - 1);
	return (index);
}

static int				ft_lowshrthd_pad(unsigned char *buffer, \
					short expon, t_print *clipb, int neg)
{
	unsigned short	nb_len;
	unsigned short	str_len;

	nb_len = ft_nbrlen((long long)expon, 10);
	str_len = ft_lowshrthd_prec(buffer, clipb);
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(str_len + 3 + nb_len, clipb) == -1)
			return (-1);
	if (ft_prefix(neg, clipb) == -1)
		return (-1);
	if (clipb->printer((const unsigned char *)"0x", 2, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == -1 && flagverif('0', clipb->flags) == 1)
		if (ft_float_precision((str_len - 1) + 3 + nb_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, (size_t)str_len, clipb) == -1)
		return (-1);
	if (flagverif('.', clipb->flags) == 1 && clipb->flags->precision >= str_len)
		if (pad_zero(clipb->flags->precision, clipb) == -1)
			return (-1);
	if (exponentbuffer(clipb, expon) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > str_len)
		if (ft_float_precision(str_len + 3 + nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static void			ft_man_to_buffer(unsigned long long mantissa, \
				unsigned char *buffer, t_print *clipb)
{
	char				*base;
	unsigned short		cur_len;
	size_t				yes;

	base = "0123456789abcdef";
	yes = 0;
	cur_len = ft_ull_len(mantissa, 16);
	while (mantissa > 16)
	{
		if ((base[(mantissa % 16)] == '0' && yes != 0) \
		|| base[(mantissa % 16)] != '0')
		{
			buffer[cur_len] = base[(mantissa % 16)];
			yes++;
		}
		if (cur_len == 2 && (buffer[cur_len + 1] != '\0' || \
		flagverif('.', clipb->flags) == 1))
		{
			cur_len--;
			buffer[cur_len] = '.';
		}
		mantissa /= 16;
		cur_len--;
	}
	buffer[cur_len] = base[mantissa];
}

int						ft_lowhexpoint(va_list args, t_print *clipb)
{
	unsigned char		buffer[20];
	t_float				conversion;
	long double			nb;
	int					neg;
	short				expon;

	neg = ft_floatconv(args, &nb, clipb->flags);
	conversion.ld = nb;
	ft_man_to_buffer(conversion.llu, buffer, clipb);
	if (nb == 0.0)
		expon = 0;
	else
		expon = (conversion.byte[4] & 0x7FFF) - 16386;
	if (ft_lowshrthd_pad(buffer, expon, clipb, neg) == -1)
		return (-1);
	return (1);
}
