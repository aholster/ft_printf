/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsigned_lowhex.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 16:34:02 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/05 18:43:30 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
static int				ft_lowhex_pad(unsigned short nb_len, t_print *clipb)
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

static int				ft_lowhex_prec(unsigned char *buffer, \
							unsigned short nb_len, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1)
	{
		if (ft_lowhex_pad(nb_len, clipb) == -1)
			return (-1);
	}
	if (flagverif('#', clipb->flags) == 1)
	{
		if (clipb->printer((const unsigned char *)"0x", 2, clipb) == -1)
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
		if (ft_lowhex_pad(nb_len, clipb) == -1)
			return (-1);
	}
	return (1);
}

static unsigned short	ft_int_len(unsigned char *buffer, int nb)
{
	unsigned long long	temp_num;
	unsigned int		num_len;
	unsigned short		cur_len;
	char				*base;

	base = "0123456789abcdef";
	temp_num = nb;
	num_len = (unsigned int)ft_nbrlen(nb, 16);
	cur_len = num_len - 1;
	if (temp_num > 0)
	{
		temp_num *= -1;
		cur_len--;
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

int						ft_unsigned_lowhex(va_list ap, t_print *clipb)
{
	unsigned char		buffer[20];
	unsigned int		nb; // change to unsigned long long and test
	unsigned short		nb_len;

	nb = (unsigned int)va_arg(ap, int); // typecast to unsigned long long and void*
	nb_len = ft_int_len(buffer, nb);
	if (flagverif('.', clipb->flags) == 1)
		return (ft_lowhex_prec(buffer, nb_len, clipb));
	if (flagverif('-', clipb->flags) == -1 && clipb->flags->padding > nb_len)
	{
		if (pad_spaces(clipb->flags->padding - nb_len, clipb) == -1)
			return (-1);
	}
	if (flagverif('#', clipb->flags) == 1 && clipb->flags->padding > nb_len)
	{
		if (clipb->printer((const unsigned char *)"0x", 2, clipb) == -1)
			return (-1);
		nb_len += 2; // test if this works.... 
	}
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1) // might need to (nb_len - 2)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > nb_len)
	{
		// if (flagverif('#', clipb->flags) == 1)
		// 	nb_len += 2;
		if (pad_spaces(clipb->flags->padding - nb_len, clipb) == -1)
			return (-1);
	}
	return (1);
}