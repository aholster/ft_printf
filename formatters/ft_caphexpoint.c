/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_caphexpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/10 12:13:37 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/02 21:27:56 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int				ft_exponbuff(char *const restrict buffer, short expon)
{
	unsigned short	index;
	int				is_neg;
	unsigned short	backup_index;

	is_neg = expon;
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
	if (is_neg < 0)
		buffer[1] = '-';
	else
		buffer[1] = '+';
	buffer[0] = 'P';
	return (backup_index + 1);
}

static int				ft_end_pad(t_writer *const restrict clipb,\
							const short expon,\
							const unsigned short nb_len,\
							unsigned short str_len)
{
	unsigned short	expon_len;
	char			buffer[8];

	if (flagverif('.', clipb->flags) == 1 && \
		clipb->flags->precision != (str_len - 2))
		if (pad_zero(clipb->flags->precision, clipb) == -1)
			return (-1);
	expon_len = ft_exponbuff(buffer, expon);
	if (clipb->self(buffer, expon_len, clipb) == -1)
		return (-1);
	if (clipb->flags->precision == 0)
		str_len--;
	if (flagverif('-', clipb->flags) == 1 \
		&& clipb->flags->padding > clipb->flags->precision)
		if (ft_float_padder(nb_len + str_len, str_len - 2, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_front_pad(const char *const restrict buffer,\
							const short expon,\
							t_writer *const restrict clipb,\
							const int is_neg)
{
	unsigned short	expon_len;
	unsigned short	str_len;
	short			nb_len;

	nb_len = is_neg;
	if (nb_len < 0)
		nb_len *= -1;
	str_len = ft_hexpoint_prec(buffer, clipb, nb_len, expon);
	expon_len = ft_nbrlen((long long)expon, 10) + 3;
	expon_len += ft_negpos_handler(clipb, is_neg, expon);
	if (flagverif('.', clipb->flags) == 1 && clipb->flags->precision == 0)
		expon_len--;
	if (flagverif('-', clipb->flags) == -1 &&\
		clipb->flags->padding > clipb->flags->precision)
		if (ft_float_padder(expon_len + str_len, str_len - 2, clipb) == -1)
			return (-1);
	if (ft_prefix(is_neg, clipb) == -1)
		return (-1);
	if (clipb->self(buffer, str_len, clipb) == -1)
		return (-1);
	if (ft_end_pad(clipb, expon, nb_len, str_len) == -1)
		return (-1);
	return (1);
}

static short			ft_ull_to_hex(unsigned long long mantissa,\
							char *const restrict buffer,\
							const t_writer *const restrict clipb,\
							const short expon)
{
	unsigned short		index;
	unsigned short		len;
	const char			*base = "0123456789ABCDEF";

	if (mantissa == 0)
		buffer[0] = '0';
	index = ft_reversed(mantissa);
	len = index;
	if ((clipb->flags->precision != 0 || expon == 1020))
		index++;
	while (index > 0)
	{
		index--;
		if (index == 1 && (clipb->flags->precision != 0 || expon == 1020))
		{
			buffer[index] = '.';
			index--;
		}
		buffer[index] = base[mantissa & 0XFLLU];
		mantissa >>= 4;
	}
	return (len);
}

int						ft_caphexpoint(va_list args,\
							t_writer *const restrict clipb)
{
	char			buffer[16];
	t_float			conversion;
	long double		nb;
	int				is_neg;
	short			expon;

	is_neg = ft_longdouble_conv(args, &nb, clipb->flags);
	conversion.ld = nb;
	if (nb == 0.0)
		is_neg *= ft_float_exceptions(buffer, &expon, clipb->flags);
	else
	{
		expon = (conversion.byte[4] & 0x7FFF) - 16386;
		is_neg *= ft_ull_to_hex(conversion.llu, buffer, clipb, expon);
	}
	ft_hexpoint_rounder(buffer, clipb, &expon);
	if (ft_front_pad(buffer, expon, clipb, is_neg) == -1)
		return (-1);
	return (1);
}
