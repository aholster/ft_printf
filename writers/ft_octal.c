/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_octal.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 15:08:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/05 18:59:14 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				ft_octal_pad(unsigned short nb_len, t_print *clipb)
{
	unsigned int diff;

	diff = clipb->flags->padding - clipb->flags->precision;
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
	return (1);
}

static int				ft_octal_prec(unsigned char *buffer,\
						 unsigned long long nb, unsigned short nb_len,\
						 t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1)
	{
		if (ft_octal_pad(nb_len, clipb) == -1)
			return (-1);
	}
	if (flagverif('.', clipb->flags) == -1 && clipb->flags->precision > nb_len)
	{
		if (pad_zero(clipb->flags->precision - nb_len, clipb) == -1)
			return (-1);
	}
	if (flagverif('.', clipb->flags) == 1 && clipb->flags->precision > nb_len)
	{
		if (pad_zero(clipb->flags->precision - nb_len, clipb) == -1)
			return (-1);
	}
	if (flagverif('.', clipb->flags) == 1 && flagverif('#', clipb->flags) == -1 && nb == 0)
			ft_strcpy((char*)buffer, " ");
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1)
			return (-1);
	if (flagverif('-', clipb->flags) == 1)
	{
		if (ft_octal_pad(nb_len, clipb) == -1)
			return (-1);
	}
	return (1);
}

static unsigned short	ft_int_len(unsigned char *buffer, \
							unsigned long long nb, t_print *clipb)
{
	unsigned long long	temp_num;
	unsigned short		num_len;
	unsigned short		cur_len;
	char				*base;

	base = "01234567";
	temp_num = nb;
	num_len = (unsigned short)ft_nbrlen(nb, 8);
	cur_len = num_len - 1;
	if (flagverif('#', clipb->flags) == 1 && clipb->flags->precision < num_len\
		 && nb != 0)
		cur_len++;
	while (temp_num >= 8)
	{
		buffer[cur_len] = base[(temp_num % 8)];
		temp_num /= 8;
		cur_len--;
	}
	buffer[cur_len] = base[temp_num];
	if (flagverif('#', clipb->flags) == 1 && clipb->flags->precision < num_len)
	{
			buffer[0] = '0';
			num_len += 1;
	}
	return (num_len);
}

int						ft_octal(va_list ap, t_print *clipb)
{
	unsigned char		buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;

	nb = (unsigned long long)va_arg(ap, void*);
	nb_len = ft_int_len(buffer, nb, clipb);
	//if (flagverif('#', clipb->flags) == -1 && nb == 0 && clipb->flags->padding == 0 && clipb->flags->precision == 0) // make seperate function for Zero
	//	return (ft_zeroval(buffer, nb, clip));
	if (flagverif('#', clipb->flags) == -1 && nb == 0\
	 && clipb->flags->padding == 0 && clipb->flags->precision == 0)
		return (1);
	if (flagverif('.', clipb->flags) == 1)
		return (ft_octal_prec(buffer, nb, nb_len, clipb));
	if (flagverif('-', clipb->flags) == -1 && clipb->flags->padding > nb_len)
	{
		if (pad_spaces(clipb->flags->padding - nb_len, clipb) == -1)
			return (-1);
	}
	if (flagverif('.', clipb->flags) == 1 && flagverif('#', clipb->flags) == -1 && nb == 0)
			ft_strcpy((char*)buffer, " ");
	if (clipb->printer(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > nb_len)
	{
		if (pad_spaces(clipb->flags->padding - nb_len, clipb) == -1)
			return (-1);
	}
	return (1);
}
