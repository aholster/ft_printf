/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shrthd_handlers.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/25 12:01:20 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/19 10:28:12 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

static int		ft_buffer_print(char *buffer,\
					t_writer *const clipb,\
					size_t *new_len,\
					size_t diff)
{
	t_flag *const	flags = clipb->flags;

	if (flg_verif('#', flags) == 1 && *new_len < flags->precision)
	{
		if (clipb->self(buffer, (*new_len + diff), clipb) == -1)
			return (-1);
		*new_len += diff;
	}
	else
	{
		if (clipb->self(buffer, *new_len, clipb) == -1)
			return (-1);
	}
	return (1);
}

static int		ft_offset_handler(char **const buffer,\
					t_writer *const clipb,\
					size_t offset)
{
	if (offset == 0)
	{
		if (clipb->self(*buffer, 1, clipb) == -1)
			return (-1);
		*buffer += 1;
	}
	return (1);
}

static int		ft_end_pad(t_writer *const clipb, \
					size_t new_len)
{
	t_flag *const	flags = clipb->flags;

	if (flg_verif('#', flags) == 1 && new_len < 7)
	{
		if (pad_zero(7 - new_len, clipb) == -1)
			return (-1);
		new_len += (7 - new_len);
	}
	if (flg_verif('-', flags) == 1)
		if (ft_space_padder(new_len, clipb) == -1)
			return (-1);
	return (1);
}

int				ft_shrthd_print(char *buffer,\
					size_t offset,\
					t_writer *const clipb,\
					size_t new_len)
{
	t_flag *const	flags = clipb->flags;
	size_t			diff;

	diff = flags->precision - new_len;
	if (flg_verif('-', flags) == -1 && \
	flg_verif('0', flags) == -1)
		if (ft_space_padder(new_len, clipb) == -1)
			return (-1);
	if (ft_offset_handler(&buffer, clipb, offset) == -1)
		return (-1);
	if (flg_verif('-', flags) == -1 && \
	flg_verif('0', flags) == 1 && flags->padding > new_len)
		if (pad_zero(flags->padding - new_len, clipb) == -1)
			return (-1);
	if (ft_buffer_print(buffer, clipb, &new_len, diff) == -1)
		return (-1);
	if (ft_end_pad(clipb, new_len) == -1)
		return (-1);
	return (1);
}

size_t			ft_shrthd_offset(char **const buffer,\
					t_writer *const clipb,\
					int is_neg)
{
	t_flag *const	flags = clipb->flags;
	size_t			offset;

	offset = 0;
	if (is_neg == 1)
	{
		if (flg_verif('+', flags) == 1)
			*buffer[0] = '+';
		else if (flg_verif(' ', flags) == 1)
			*buffer[0] = ' ';
		else if (flg_verif('+', flags) == -1 \
		&& flg_verif(' ', flags) == -1)
			offset++;
	}
	else
		*buffer[0] = '-';
	*buffer += offset;
	return (offset);
}
