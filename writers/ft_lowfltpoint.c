/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowfltpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/09 13:45:41 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/20 13:16:00 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static size_t 	ft_x_offset(char *buffer, size_t *nb_len, \
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
				nb_len -= 1;
			}
		}
		else
			buffer[0] = '-';
	}
	return (offset);
}

static int		ft_float_padding(char * buffer, t_print *const clipb, \
			size_t nb_len, int neg)
{
	size_t offset;

	offset = ft_x_offset(buffer, &nb_len, clipb, neg);
	nb_len -= offset;
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == 1)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer + offset, nb_len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

int				ft_lowfltpoint(va_list args, t_print *const clipb)
{
	char				*buffer;
	long double			nb;
	size_t				nb_len;
	int					neg;
	int					ret_hold;

	neg = ft_longdouble_conv(args, &nb, clipb->flags);
	if (flagverif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	if (ft_custom_ld_to_text(nb, \
	clipb->flags->precision, &buffer, &nb_len) == -1)
		return (-1);
	if (clipb->flags->precision == 0)
		nb_len--;
	ft_buffer_rounder(buffer, clipb, nb_len);
	nb_len--;
	ret_hold = ft_float_padding(buffer, clipb, nb_len, neg);
	free(buffer);
	return (ret_hold);
}
