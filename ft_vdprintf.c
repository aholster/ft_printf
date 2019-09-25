/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vdprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/19 14:43:08 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/25 14:37:25 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static void	ft_write_history(const int fd, const char *const restrict mem,\
						const size_t size, t_writer *const restrict clipb)
{
	write(fd, mem, size);
	clipb->history += size;
	clipb->current = 0;
}

static int	ft_bufmanager(const char *restrict mem,\
							size_t size, t_writer *const restrict clipb)
{
	size_t		block;
	t_d_write	*info;
	int			fd;

	info = clipb->info.d;
	fd = info->fd;
	if (mem == NULL)
		ft_write_history(fd, info->buffer, clipb->current, clipb);
	else
		while (size > 0)
		{
			if (size + clipb->current <= BUFFSIZE)
				block = size;
			else
				block = (BUFFSIZE - clipb->current);
			ft_memcpy(info->buffer + clipb->current, mem, block);
			clipb->current += block;
			mem += block;
			size -= block;
			if (clipb->current == BUFFSIZE)
				ft_write_history(fd, info->buffer, BUFFSIZE, clipb);
		}
	return (0);
}

static int	ft_vd_clipb_init(va_list args, const int fd,\
				t_wrt_ptr printer, t_writer *const restrict clipb)
{
	t_d_write	*info;

	info = clipb->info.d;
	va_copy(clipb->args, args);
	clipb->history = 0;
	clipb->current = 0;
	clipb->self = printer;
	info->fd = fd;
	return (1);
}

int			ft_vdprintf(const int fd, const char *restrict format, va_list args)
{
	t_writer	clipb;
	t_d_write	info;

	clipb.info.d = &info;
	if (ft_vd_clipb_init(args, fd, ft_bufmanager, &clipb) == -1)
		return (-1);
	if (ft_format(format, &clipb) == -1)
	{
		return (-1);
	}
	ft_bufmanager(NULL, 0, &clipb);
	va_copy(args, clipb.args);
	va_end(clipb.args);
	return (clipb.history);
}
