/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowshrthd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/21 12:57:35 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/19 16:12:58 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static size_t		ft_x_offset(char *buffer, size_t *nb_len, \
				t_print *const restrict clipb, int neg)
{
	size_t offset;

	offset = 0;
	if (buffer[0] == 'X')
	{
		if (neg == 1)
		{
			if (flagverif('+', clipb->flags) == 1)
				buffer[0] = '+';
			else if (flagverif(' ', clipb->flags) == 1 && \
			flagverif('+', clipb->flags) == -1)
				buffer[0] = ' ';
			else if (flagverif('+', clipb->flags) == -1 \
			&& flagverif(' ', clipb->flags) == -1)
			{
				offset++;
				*nb_len -= 1;
			}
		}
		else
			buffer[0] = '-';
	}
	return (offset);
}

static size_t		ft_shorthand_prec(char *buffer, \
				size_t nb_len, size_t offset, t_print *const restrict clipb)
{
	size_t	index;
	size_t	holder;
	size_t	new_len;

	new_len = nb_len;
	index = nb_len;
	holder = 0;
	while (buffer[index] == '0' && buffer[index] != '.')
	{
		holder = index;
		index--;
	}
	if (buffer[index] == '.')
		holder--;
	if (nb_len > holder && holder > 0)
		new_len = holder - offset;
	else if (new_len == holder)
		new_len = clipb->flags->precision;
	return (new_len);
}

static int			ft_float_padding(char *buffer, \
				int neg, t_print *const clipb, size_t nb_len)
{
	size_t	offset;
	size_t	new_len;

	offset = ft_x_offset(buffer, &nb_len, clipb, neg);
	new_len = ft_shorthand_prec(buffer, nb_len, offset, clipb);
	clipb->flags->precision = new_len;
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(new_len, clipb) == -1)
			return (-1);
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == 1)
		if (ft_zero_padder(new_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer + offset, new_len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1)
		if (ft_space_padder(new_len, clipb) == -1)
			return (-1);
	return (1);
}

int					ft_lowshrthd(va_list args, t_print *const clipb)
{
	char				*buffer;
	long double			nb;
	size_t				nb_len;
	int					neg;
	int					ret_val;

	neg = ft_longdouble_conv(args, &nb, clipb->flags);
	if (flagverif('.', clipb->flags) == 1 && clipb->flags->precision <= 1)
	{
		if (ft_lowsci(args, clipb) == -1)
			return (-1);
		return (1);
	}
	if (flagverif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	if (ft_custom_ld_to_text(nb, \
	clipb->flags->precision, &buffer, &nb_len) == -1)
		return (-1);
	ft_buffer_rounder(buffer, clipb, nb_len);
	nb_len--;
	ret_val = ft_float_padding(buffer, neg, clipb, nb_len);
	free(buffer);
	return (ret_val);
}
