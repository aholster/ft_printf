/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handling.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/06 10:44:11 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/01 19:36:41 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/ft_internals.h"

void				ft_shorthand_prec(const char *const restrict buffer,\
						const unsigned short nb_len,\
						const t_writer *const restrict clipb)
{
	size_t index;
	size_t holder;

	index = nb_len;
	holder = 0;
	while (index < clipb->flags->precision)
	{
		while (buffer[index] != '0' && index < clipb->flags->precision + 1)
			index++;
		if (buffer[index] == '0' && index < clipb->flags->precision + 1)
		{
			holder = index - 1;
			while (buffer[index] == '0' && index < clipb->flags->precision + 1)
				index++;
		}
	}
	if (index > holder && holder != 0)
		clipb->flags->precision = index - holder;
}

unsigned short		ft_lowhexpoint_prec(const char *const restrict buffer,\
						const t_writer *const restrict clipb)
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
	dec_len = index - dec_len - 1;
	if (flagverif('.', clipb->flags) == 1)
	{
		if (clipb->flags->precision == 0)
			index++;
		if (dec_len > clipb->flags->precision && dec_len < index)
			index = (index - dec_len) + clipb->flags->precision;
		else if (dec_len < clipb->flags->precision)
			clipb->flags->precision -= dec_len;
	}
	return (index);
}

int					ft_prefix(const int neg, t_writer *const restrict clipb)
{
	if (neg >= 0)
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
	else if (clipb->self("-", 1, clipb) == -1)
		return (-1);
	return (1);
}

unsigned short		ft_ull_len(unsigned long long num, const int base)
{
	unsigned short length;

	length = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= base;
		length++;
	}
	return (length);
}

void				ft_float_exceptions(char *const restrict buffer,\
					const long double nb,\
					short *const restrict expon,\
					const t_writer *const restrict clipb)
{
	if (nb == 0.0)
	{
		*expon = 0;
		buffer[0] = '0';
		if (clipb->flags->precision != 0)
		{
			buffer[1] = '.';
			buffer[2] = '0';
		}
	}
}
