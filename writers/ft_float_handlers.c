/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_float_handlers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/17 12:34:56 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/27 17:14:09 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"
#include <stdio.h>
size_t			ft_x_offset(char **buffer, size_t *nb_len, \
			t_print *const restrict clipb, int neg)
{
	size_t	offset;

	offset = 0;
	(void)nb_len;
	if (neg == 1)
	{
		if (flagverif('+', clipb->flags) == 1)
			*buffer[0] = '+';
		else if (flagverif(' ', clipb->flags) == 1)
			*buffer[0] = ' ';
		else if (flagverif('+', clipb->flags) == -1 \
		&& flagverif(' ', clipb->flags) == -1)
			offset++;
	}
	else
		*buffer[0] = '-';
	*buffer += offset;
	if (offset == 1)
		*nb_len -= 1;
	return (offset);
}

int				ft_expon_finder(char *buffer, size_t nb_len)
{
	int			index;
	size_t		one_dex;

	index = 0;
	while (buffer[index] != '.')
		index++;
	one_dex = index + 1;
	ft_memmove(buffer + index, buffer + one_dex, nb_len);
	ft_memmove(buffer + 3, buffer + 2, nb_len);
	buffer[2] = '.';
	index -= 2;
	return (index);
}

void		ft_float_exceptions(char *buffer, long double nb, \
		short *expon, t_print *const clipb)
{
	if (nb == 0.0)
	{
		expon = 0;
		buffer[0] = '0';
		if (clipb->flags->precision != 0)
		{
			buffer[1] = '.';
			buffer[2] = '0';
		}
	}
}

void		ft_expon_len(char *buffer, size_t *new_len, \
		t_print *const restrict clipb, int neg)
{
	size_t			index;
	size_t			holder;
	unsigned int	precision;

	(void)neg;
	index = 0;
	precision = clipb->flags->precision;
	while (buffer[index] != '.')
		index++;
	index++;
	if (precision > index)
	{
		holder = precision - index;
		*new_len = index + holder + 1;
	}
	else if (precision == index)
		*new_len = index + 1;
	else if (precision < index && precision != 0)
		*new_len = precision + 1;
	else if (precision == 0)
		*new_len = 8;
}
