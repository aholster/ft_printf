/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsigned_caphex.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 18:20:19 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/03 18:21:33 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
static int				flagverif(const unsigned char c, const t_flag *flags)
{
	unsigned short	flip;

	flip = c / 64;
	if (((1LLU << (c - (flip * 64))) & flags->actiflags[flip]) > 0)
		return (1);
	return (-1);
}

static int				ft_caphex_pad(unsigned short nb_len, t_print *clipb)
{
	unsigned int diff;

	diff = clipb->flags->padding - clipb->flags->precision;
	if (flagverif('#', clipb->flags) == 1)
		diff -= 2;
	if (clipb->flags->precision < 1)
	{
		if (diff > nb_len)
		{
			if (pad_spaces((diff - nb_len), clipb) == -1)
				return (-1);
		}
	}
	else if (clipb->flags->padding > clipb->flags->precision)
	{
		if (pad_spaces(diff, clipb) == -1)
			return (-1);
	}
	return (0);
}

static int				ft_caphex_prec(unsigned char *buffer, \
							unsigned short nb_len, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1)
	{
		if (ft_caphex_pad(nb_len, clipb) == -1)
			return (-1);
	}
	if (flagverif('#', clipb->flags) == 1)
	{
		if (clipb->printer((const unsigned char *)"0X", 2, clipb) == -1)
			return (-1);
	}
	if (clipb->flags->precision > nb_len)
	{
		if (pad_zero(clipb->flags->precision - (nb_len), clipb) == -1)
			return (-1);
	}
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1)
	{
		if (ft_caphex_pad(nb_len, clipb) == -1)
			return (-1);
	}
	return (1);
}

static unsigned short	ft_int_len(unsigned char *buffer, unsigned long long nb)
{
	unsigned long long	temp_num;
	unsigned short		num_len;
	unsigned short		cur_len;
	char				*base;

	base = "0123456789ABCDEF";
	temp_num = nb;
	num_len = (unsigned short)ft_nbrlen(nb, 16) - 1;
	cur_len = num_len;
	while (temp_num >= 8)
	{
		buffer[cur_len] = base[(temp_num % 16)];
		temp_num /= 16;
		cur_len--;
	}
	buffer[cur_len] = base[temp_num];
	return (num_len + 1);
}

int						ft_unsigned_caphex(va_list ap, t_print *clipb)
{
	unsigned char		buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;

	nb = (unsigned long long)va_arg(ap, void*);
	nb_len = ft_int_len(buffer, nb);
	if (flagverif('.', clipb->flags) == 1)
		return (ft_caphex_prec(buffer, nb_len, clipb));
	if (flagverif('-', clipb->flags) == -1 && clipb->flags->padding > nb_len)
	{
		if (pad_spaces(clipb->flags->padding - nb_len, clipb) == -1)
			return (-1);
	}
	if (flagverif('#', clipb->flags) == 1 && clipb->flags->padding > nb_len)
	{
		if (clipb->printer((const unsigned char *)"0X", 2, clipb) == -1)
			return (-1);
	}
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > nb_len)
	{
		if (flagverif('#', clipb->flags) == 1)
			nb_len += 2;
		if (pad_spaces(clipb->flags->padding - nb_len, clipb) == -1)
			return (-1);
	}
	return (1);
}