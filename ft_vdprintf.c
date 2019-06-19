/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vdprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/19 14:43:08 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/19 15:33:18 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_write_history(const unsigned char *mem, const size_t size,\
								t_print *clipb)
{
	write(clipb->fd, mem, size);
	clipb->history += size;
	clipb->current = 0;
}

static int	ft_bufmanager(const unsigned char *mem, size_t size, t_print *clipb)
{
	size_t	block;

	if (mem == NULL)
		ft_write_history((const unsigned char *)clipb->buffer, clipb->current, clipb);
	else
		while (size > 0)
		{
			if (clipb->current == BUFFSIZE)
				ft_write_history((const unsigned char *)clipb->buffer, BUFFSIZE, clipb);
			if (size + clipb->current <= BUFFSIZE)
				block = size;
			else
				block = (BUFFSIZE - clipb->current);
			ft_memcpy(clipb->buffer + clipb->current, mem, block);
			clipb->current += block;
			mem += block;
			size -= block;
		}
	return (0);
}

static int	ft_vd_clipb_init(va_list args, const int fd, t_wrt_ptr printer, t_print *clipb)
{
	clipb->alst = NULL;
	va_copy(clipb->origin_args, args);
	va_copy(clipb->args, args);
	clipb->history = 0;
	clipb->current = 0;
	clipb->fd = fd;
	clipb->printer = printer;
	clipb->buffer = (char *)malloc(sizeof(char) * BUFFSIZE);
	if (clipb->buffer == NULL)
		return (-1);
	return (1);
}

int			ft_vdprintf(const int fd, const char *format, va_list args)
{
	t_print		clipb;

	if (ft_vd_clipb_init(args, fd, ft_bufmanager, &clipb) == -1)
		return (-1);
	if (ft_format((unsigned char *)format, &clipb) == -1)
	{
		free(clipb.buffer);
		return (-1);
	}
	ft_bufmanager(NULL, 0, &clipb);
	free(clipb.buffer);
	va_end(clipb.origin_args);
	va_end(clipb.args);
	return (clipb.history);
}
