/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowhexpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/28 14:42:40 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/27 18:38:31 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static int					ft_expon_buff(char *buffer, short expon)
{
	unsigned short	index;
	int				neg;
	unsigned short	backup_index;

	neg = expon;
	index = ft_nbrlen((long long)expon, 10);
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
	buffer[0] = 'p';
	return (backup_index + 1);
}

static int					ft_end_pad(t_print *const clipb, short expon, \
						unsigned short nb_len, unsigned short str_len)
{
	unsigned short	expon_len;
	char			buffer[8];

	if (flagverif('.', clipb->flags) == 1 && \
	clipb->flags->precision != (str_len - 2))
		if (pad_zero(clipb->flags->precision, clipb) == -1)
			return (-1);
	expon_len = ft_expon_buff(buffer, expon);
	if (clipb->printer(buffer, expon_len, clipb) == -1)
		return (-1);
	if (clipb->flags->precision == 0)
		str_len--;
	if (flagverif('-', clipb->flags) == 1 \
	&& clipb->flags->padding > clipb->flags->precision)
		if (ft_float_padder(nb_len + str_len, str_len - 2, clipb) == -1)
			return (-1);
	return (1);
}

static int					ft_front_pad(char *buffer, \
					short expon, t_print *const clipb, int neg)
{
	unsigned short	expon_len;
	unsigned short	str_len;

	str_len = ft_lowhexpoint_prec(buffer, clipb);
	expon_len = ft_nbrlen((long long)expon, 10) + 3;
	if (expon >= 0)
		expon_len++;
	expon_len += ft_negpos_handler(clipb, neg);
	if (flagverif('.', clipb->flags) == 1 && clipb->flags->precision == 0)
		expon_len--;
	if (flagverif('-', clipb->flags) == -1 && \
	clipb->flags->padding > clipb->flags->precision)
		if (ft_float_padder(expon_len + str_len, str_len - 2, clipb) == -1)
			return (-1);
	if (ft_prefix(neg, clipb) == -1)
		return (-1);
	if (clipb->printer("0x", 2, clipb) == -1)
		return (-1);
	if (clipb->printer(buffer, str_len, clipb) == -1)
		return (-1);
	if (ft_end_pad(clipb, expon, expon_len, str_len) == -1)
		return (-1);
	return (1);
}

static void					ft_man_to_buffer(unsigned long long mantissa,\
						char *buffer, t_print *const clipb, short expon)
{
	char				*base;
	unsigned short		cur_len;
	size_t				buffer_trim;

	base = "0123456789abcdef";
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
		if (cur_len == 2 && (clipb->flags->precision != 0 || expon == 1020))
		{
				cur_len--;
				buffer[cur_len] = '.';
		}
		mantissa /= 16;
		cur_len--;
	}
	buffer[cur_len] = base[mantissa];
}

int							ft_lowhexpoint(va_list args, t_print *const restrict clipb)
{
	char			buffer[18];
	t_float			conversion;
	long double		nb;
	int				neg;
	short			expon;

	neg = ft_longdouble_conv(args, &nb, clipb->flags);
	conversion.ld = nb;
	if (nb == 0.0)
		ft_float_exceptions(buffer, nb, &expon, clipb);
	else
	{
		expon = (conversion.byte[4] & 0x7FFF) - 16386;
		ft_man_to_buffer(conversion.llu, buffer, clipb, expon);
	}
	ft_hexpoint_rounder(buffer, clipb, &expon);
	if (ft_front_pad(buffer, expon, clipb, neg) == -1)
		return (-1);
	return (1);
}
