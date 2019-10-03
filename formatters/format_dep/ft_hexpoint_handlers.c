/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hexpoint_handlers.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/06 10:44:11 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/03 14:48:15 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

int					ft_prefix(int is_neg, t_writer *const clipb)
{
	if (is_neg >= 0)
	{
		if (flagverif('+', clipb->flags) == 1)
			if (clipb->self("+", 1, clipb) == -1)
				return (-1);
		if (flagverif(' ', clipb->flags) == 1 && \
		flagverif('+', clipb->flags) == -1)
		{
			if (clipb->self(" ", 1, clipb) == -1)
				return (-1);
		}
	}
	else if (is_neg < 0)
		if (clipb->self("-", 1, clipb) == -1)
			return (-1);
	return (1);
}

static int	ft_caphexponbuff(char *buffer, short expon)
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

int				ft_caphexpoint_print(t_writer *const restrict clipb,\
						short expon,\
						unsigned short nb_len,
						unsigned short str_len)
{
	unsigned short	expon_len;
	char			new_buf[8];

	if (flagverif('.', clipb->flags) == 1 && \
	clipb->flags->precision != (str_len - 2))
		if (pad_zero(clipb->flags->precision, clipb) == -1)
			return (-1);
	expon_len = ft_caphexponbuff(new_buf, expon);
	if (clipb->self(new_buf, expon_len, clipb) == -1)
		return (-1);
	if (clipb->flags->precision == 0)
		str_len--;
	if (flagverif('-', clipb->flags) == 1 \
	&& clipb->flags->padding > clipb->flags->precision)
		if (ft_float_padder(nb_len + str_len, str_len - 2, clipb) == -1)
			return (-1);
	return (1);
}

static int	ft_lowhexponbuff(char *buffer, short expon)
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
	buffer[0] = 'p';
	return (backup_index + 1);
}

int				ft_lowhexpoint_print(t_writer *const restrict clipb,\
						short expon,\
						unsigned short nb_len,
						unsigned short str_len)
{
	unsigned short	expon_len;
	char			new_buf[8];

	if (flagverif('.', clipb->flags) == 1 && \
	clipb->flags->precision != (str_len - 2))
		if (pad_zero(clipb->flags->precision, clipb) == -1)
			return (-1);
	expon_len = ft_lowhexponbuff(new_buf, expon);
	if (clipb->self(new_buf, expon_len, clipb) == -1)
		return (-1);
	if (clipb->flags->precision == 0)
		str_len--;
	if (flagverif('-', clipb->flags) == 1 \
	&& clipb->flags->padding > clipb->flags->precision)
		if (ft_float_padder(nb_len + str_len, str_len - 2, clipb) == -1)
			return (-1);
	return (1);
}
