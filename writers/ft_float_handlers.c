/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_float_handlers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/17 12:34:56 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/01 10:55:57 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

size_t		ft_x_offset(char **buffer, size_t *nb_len, \
		t_print *const restrict clipb, int neg)
{
	size_t	offset;

	offset = 0;
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
	else if (neg == -1)
		*buffer[0] = '-';
	*buffer += offset;
	if (offset == 1)
		*nb_len -= 1;
	return (offset);
}

size_t		ft_float_exceptions(char *buffer, long double nb, \
		short *expon, t_print *const clipb)
{
	expon = 0;
	(void)nb;
	buffer[0] = '0';
	if (clipb->flags->precision != 0)
	{
		buffer[1] = '.';
		buffer[2] = '0';
	}
	return (3);
}
