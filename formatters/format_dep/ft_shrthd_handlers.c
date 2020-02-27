/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shrthd_handlers.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/25 12:01:20 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 11:15:39 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

static void		ft_buffer_print(char *buffer,\
					t_writer *const clipb,\
					size_t *new_len,\
					size_t diff)
{
	t_flag *const	flags = clipb->flags;

	if (flg_verif('#', flags) == 1 && *new_len < flags->precision)
	{
		ft_write_wrap(buffer, (*new_len + diff), clipb);
		*new_len += diff;
	}
	else
	{
		ft_write_wrap(buffer, *new_len, clipb);
	}
}

static void		ft_offset_handler(char **const buffer,\
					t_writer *const clipb,\
					size_t offset)
{
	if (offset == 0)
	{
		ft_write_wrap(*buffer, 1, clipb);
		*buffer += 1;
	}
}

static void		ft_end_pad(t_writer *const clipb, \
					size_t new_len)
{
	t_flag *const	flags = clipb->flags;

	if (flg_verif('#', flags) == 1 && new_len < 7)
	{
		pad_zero(7 - new_len, clipb);
		new_len += (7 - new_len);
	}
	if (flg_verif('-', flags) == 1)
	{
		ft_space_padder(new_len, clipb);
	}
}

void			ft_shrthd_print(char *buffer,\
					size_t offset,\
					t_writer *const clipb,\
					size_t new_len)
{
	t_flag *const	flags = clipb->flags;
	size_t			diff;

	diff = flags->precision - new_len;
	if (flg_verif('-', flags) == -1 && \
		flg_verif('0', flags) == -1)
	{
		ft_space_padder(new_len, clipb);
	}
	ft_offset_handler(&buffer, clipb, offset);
	if (flg_verif('-', flags) == -1 && \
		flg_verif('0', flags) == 1 && flags->padding > new_len)
	{
		pad_zero(flags->padding - new_len, clipb);
	}
	ft_buffer_print(buffer, clipb, &new_len, diff);
	ft_end_pad(clipb, new_len);
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
		{
			offset++;
		}
	}
	else
	{
		*buffer[0] = '-';
	}
	*buffer += offset;
	return (offset);
}
