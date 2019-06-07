/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowhex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 16:34:02 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/07 16:36:05 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
static int				ft_lowhex_pad(unsigned short nb_len, \
						t_print *clipb)
{
	unsigned int diff;

	diff = clipb->flags->padding - clipb->flags->precision;
	if (clipb->flags->padding > nb_len)
	{
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
	}
	return (1);
}

static int				ft_no_precision(unsigned char *buffer, \
						unsigned long long nb, unsigned short nb_len, \
						t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1 && flagverif('0', clipb->flags) == -1)
	{
		if (pad_spaces(clipb->flags->padding - nb_len, clipb) == -1)
			return (-1);
	}
	if (flagverif('#', clipb->flags) == 1 && /*clipb->flags->padding > nb_len \
	&& */nb != 0)
	{
		if (clipb->printer((const unsigned char *)"0x", 2, clipb) == -1)
			return (-1);
	}
	if (flagverif('0', clipb->flags) == 1)
	{
		if ((clipb->flags->padding - clipb->flags->precision) > nb_len)
		{
			if (pad_zero((clipb->flags->padding - clipb->flags->precision - nb_len), clipb) == -1)
				return (-1);
		}
	}
	if (clipb->printer(buffer, ((size_t)nb_len), clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1)
	{
		if (pad_spaces(clipb->flags->padding - nb_len, clipb) == -1)
			return (-1);
	}
	return (1);
}

static int				ft_lowhex_prec(unsigned char *buffer, \
						unsigned long long nb, unsigned short nb_len, \
						t_print *clipb)
{
	// printf("clipb->flags->padding : %u\n", clipb->flags->padding);
	// getchar();
	if (flagverif('-', clipb->flags) == -1 && clipb->flags->padding > 0)
	{
		if (ft_lowhex_pad(nb_len, clipb) == -1)
			return (-1);
	}
	if (nb == 0 && clipb->flags->precision == 0)
		ft_strcpy((char*)buffer, " ");
	if (flagverif('#', clipb->flags) == 1 && nb != 0)
	{
		if (clipb->printer((const unsigned char *)"0x", 2, clipb) == -1)
			return (-1);
	}
	if (clipb->flags->precision > nb_len)
	{
		if (pad_zero((clipb->flags->precision - nb_len), clipb) == -1)
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

static unsigned short	ft_int_len(unsigned char *buffer, \
							unsigned long long nb)
{
	unsigned long long	temp_num;
	unsigned short		num_len;
	unsigned short		cur_len;
	char				*base;

	base = "0123456789abcdef";
	temp_num = nb;
	num_len = (unsigned short)ft_nbrlen(nb, 16);
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
	printf("buffer: %s\n", buffer);
	return (num_len);
}

int						ft_lowhex(va_list ap, t_print *clipb)
{
	unsigned char		buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;

	if (ft_signconv(ap, &nb, clipb->flags) == -1)
		nb = -nb;
	printf("nb : %llu", nb);
	nb_len = ft_int_len(buffer, nb);
	if (flagverif('#', clipb->flags) == 1)
		clipb->flags->padding -=2;
	if (nb == 0 && clipb->flags->padding == 0 && flagverif('.', clipb->flags) == 1)
		return (1);
	if (flagverif('.', clipb->flags) == 1)
		return (ft_lowhex_prec(buffer, nb, nb_len, clipb));
	if (ft_no_precision(buffer, nb, nb_len, clipb) == -1)
		return (-1);
	return (1);
}
