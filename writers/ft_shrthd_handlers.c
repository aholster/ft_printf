/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shrthd_handlers.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/25 12:01:20 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/30 12:12:24 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static int		ft_buffer_print(char *buffer, t_print *const clipb, \
			size_t *new_len, size_t diff)
{
	if (flagverif('#', clipb->flags) == 1 && *new_len < clipb->flags->precision)
	{
		if (clipb->printer(buffer, (*new_len + diff), clipb) == -1)
			return (-1);
		*new_len += diff;
	}
	else
	{
		if (clipb->printer(buffer, *new_len, clipb) == -1)
			return (-1);
	}
	return (1);
}

static int		ft_offset_handler(char **buffer, \
		t_print *const clipb, size_t offset)
{
	if (offset == 0)
	{
		if (clipb->printer(*buffer, 1, clipb) == -1)
			return (-1);
		*buffer += 1;
	}
	return (1);
}

static int		ft_end_pad(t_print *const clipb, \
			size_t new_len, size_t offset)
{
	(void)offset;
	if (flagverif('#', clipb->flags) == 1 && new_len < 7)
	{	
		if (pad_zero(7 - new_len, clipb) == -1)
			return (-1);
		new_len += (7 - new_len);
	}
	if (flagverif('-', clipb->flags) == 1)
		if (ft_space_padder(new_len, clipb) == -1)
			return (-1);
	return (1);
}

int				ft_shrthd_print(char *buffer, \
			size_t offset, t_print *const clipb, size_t new_len)
{
	size_t diff;

	diff = clipb->flags->precision - new_len;
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(new_len, clipb) == -1)
			return (-1);
	if (ft_offset_handler(&buffer, clipb, offset) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == 1 && clipb->flags->padding > new_len)
		if (pad_zero(clipb->flags->padding - new_len, clipb) == -1)
			return (-1);
	if (ft_buffer_print(buffer, clipb, &new_len, diff) == -1)
		return (-1);
	if (ft_end_pad(clipb, new_len, offset) == -1)
		return (-1);
	return (1);
}

size_t			ft_shrthd_offset(char **buffer, size_t *nb_len, \
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
	return (offset);
}
