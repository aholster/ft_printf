/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_caphexpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/10 12:13:37 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/11 10:41:02 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int					exponentbuffer(t_print *clipb, short expon)
{
	unsigned char	buffer[8];
	size_t			index;
	int				neg;
	size_t			backup_index;

	neg = expon;
	index = (size_t)ft_nbrlen((long long)expon, 10);
	if (expon < 0)
		expon *= -1;
	else 
		index++;
	backup_index = index;
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
	buffer[0] = 'P';
	if (clipb->printer(buffer, backup_index + 1, clipb) == -1)
		return (-1);
	return (1);
}

static int					ft_end_pad(t_print *clipb, short expon, \
						 unsigned short nb_len, unsigned short str_len)
{
	if (flagverif('.', clipb->flags) == 1 && \
	clipb->flags->precision != (str_len - 2))
		if (pad_zero(clipb->flags->precision, clipb) == -1)
			return (-1);
	if (exponentbuffer(clipb, expon) == -1)
		return (-1);
	if (clipb->flags->precision == 0)
		str_len--;
	if (flagverif('-', clipb->flags) == 1 \
	&& clipb->flags->padding > clipb->flags->precision)
		if (ft_float_pad(nb_len + str_len, str_len, clipb) == -1)
			return (-1);
	return (1);
}

static int					ft_front_pad(unsigned char *buffer, \
					short expon, t_print *clipb, int neg)
{
	unsigned short	nb_len;
	unsigned short	str_len;

	str_len = ft_lowhexpoint_prec(buffer, clipb);
	nb_len = ft_nbrlen((long long)expon, 10) + 3;
	if (expon >= 0)
		nb_len++;
	if (neg < 0)
		nb_len++;
	if (flagverif('.', clipb->flags) == 1 && clipb->flags->precision == 0)
		nb_len--;
	if (flagverif('-', clipb->flags) == -1 && \
	clipb->flags->padding > clipb->flags->precision)
		if (ft_float_pad(nb_len + str_len, str_len, clipb) == -1)
			return (-1);
	if (ft_prefix(neg, clipb) == -1)
		return (-1);
	if (clipb->printer((const unsigned char *)"0X", 2, clipb) == -1)
		return (-1);
	if (clipb->printer(buffer, str_len, clipb) == -1)
		return (-1);
	if (ft_end_pad(clipb, expon, nb_len, str_len) == -1)
		return (-1);
	return (1);
}

static void					ft_man_to_buffer(unsigned long long mantissa, \
				unsigned char *buffer, t_print *clipb)
{
	char				*base;
	unsigned short		cur_len;
	size_t				buffer_trim;

	base = "0123456789ABCDEF";
	buffer_trim = 0;
	cur_len = ft_ull_len(mantissa, 16);
	while (mantissa > 16)
	{
		if ((base[(mantissa % 16)] == '0' && buffer_trim != 0) \
		|| base[(mantissa % 16)] != '0')
		{
			buffer[cur_len] = base[(mantissa % 16)];
			buffer_trim++;
		}
		if (cur_len == 2 && clipb->flags->precision != 0)
		{
			cur_len--;
			buffer[cur_len] = '.';
		}
		mantissa /= 16;
		cur_len--;
	}
	buffer[cur_len] = base[mantissa];
}

int							ft_caphexpoint(va_list args, t_print *clipb)
{
	unsigned char		buffer[20];
	t_float			conversion;
	long double			nb;
	int					neg;
	short				expon;

	neg = ft_longdouble_conv(args, &nb, clipb->flags);
	conversion.ld = nb;
	if (nb == 0.0)
		ft_exceptions(buffer, nb, &expon, clipb);
	else
	{
		expon = (conversion.byte[4] & 0x7FFF) - 16386;
		ft_man_to_buffer(conversion.llu, buffer, clipb);
	}
	if (ft_front_pad(buffer, expon, clipb, neg) == -1)
		return (-1);
	return (1);
}