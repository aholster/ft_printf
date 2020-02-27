/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vdprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/19 14:43:08 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 13:27:09 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static int	ft_bufmanager(const char *mem,
				size_t size,
				t_writer *const clipb)
{
	size_t		free_space;
	char *const	dest_mem = clipb->info.d.buffer;

	while (1)
	{
		free_space = BUFFSIZE - clipb->current;
		if (size < free_space)
		{
			ft_memcpy(dest_mem + clipb->current, mem, size);
			clipb->current += size;
			break ;
		}
		else
		{
			ft_memcpy(dest_mem + clipb->current, mem, free_space);
			if (write(clipb->info.d.fd, dest_mem, BUFFSIZE) == -1)
				return (-1);
			clipb->current = 0;
			size -= free_space;
			mem += free_space;
			clipb->history += BUFFSIZE;
		}
	}
	return (0);
}

int			ft_vdprintf(const int fd, const char *format, va_list args)
{
	t_writer	clipb;

	ft_bzero(&clipb, sizeof(t_writer));
	clipb.info.d.fd = fd;
	va_copy(clipb.args, args);
	clipb.self = &ft_bufmanager;
	ft_format(format, &clipb);
	if (clipb.current != 0)
	{
		if (write(fd, clipb.info.d.buffer, clipb.current) == -1)
		{
			clipb.err = 1;
		}
		clipb.history += clipb.current;
	}
	va_copy(args, clipb.args);
	va_end(clipb.args);
	if (clipb.err == 0)
	{
		return (clipb.history);
	}
	return (-1);
}
