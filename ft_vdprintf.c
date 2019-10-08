/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vdprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/19 14:43:08 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/08 19:01:05 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static int	ft_bufmanager(const char *restrict mem,\
				size_t size,\
				t_writer *const restrict clipb)
{
	size_t					used_space;
	size_t					free_space;
	char *const restrict	dest_mem = (clipb->info.d)->buffer;

	while (1)
	{
		used_space = clipb->current;
		free_space = BUFFSIZE - used_space;
		if (size < free_space)
		{
			ft_memcpy(dest_mem + used_space, mem, size);
			clipb->current += size;
			break ;
		}
		else
		{
			ft_memcpy(dest_mem + used_space, mem, free_space);
			write((clipb->info.d)->fd, dest_mem, BUFFSIZE);
			clipb->current = 0;
			size -= free_space;
			mem += free_space;
			clipb->history += BUFFSIZE;
		}
	}
	return (0);
}

static int	ft_vd_clipb_init(va_list args,\
				const int fd,\
				t_wrt_ptr printer,\
				t_writer *const restrict clipb)
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
	if (clipb.current != 0)
	{
		write(fd, info.buffer, clipb.current);
		clipb.history += clipb.current;
	}
	va_copy(args, clipb.args);
	va_end(clipb.args);
	return (clipb.history);
}
