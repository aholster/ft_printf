/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:14 by aholster       #+#    #+#                */
/*   Updated: 2019/06/11 19:22:55 by aholster      ########   odam.nl         */
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

int			ft_printf(char *format, ...)
{
	va_list		ap;
	t_print		clipb;

	va_start(ap, format);
	if (ft_clinit(NULL, 1, ft_bufmanager, &clipb) == -1)
		return (-1);
	if (ft_format(ap, (unsigned char *)format, &clipb) == -1)
	{
		free(clipb.buffer);
		return (-1);
	}
	ft_bufmanager(NULL, 0, &clipb);
	free(clipb.buffer);
	va_end(ap);
	return (clipb.history);
}

int			ft_dprintf(const int fd, char *format, ...)
{
	va_list		ap;
	t_print		clipb;

	va_start(ap, format);
	if (ft_clinit(NULL, fd, ft_bufmanager, &clipb) == -1)
		return (-1);
	if (ft_format(ap, (unsigned char *)format, &clipb) == -1)
	{
		free(clipb.buffer);
		return (-1);
	}
	ft_bufmanager(NULL, 0, &clipb);
	free(clipb.buffer);
	va_end(ap);
	return (clipb.history);
}

int			ft_vprintf(char *format, va_list ap)
{
	t_print		clipb;

	if (ft_clinit(NULL, 1, ft_bufmanager, &clipb) == -1)
		return (-1);
	if (ft_format(ap, (unsigned char *)format, &clipb) == -1)
	{
		free(clipb.buffer);
		return (-1);
	}
	ft_bufmanager(NULL, 0, &clipb);
	free(clipb.buffer);
	va_end(ap);
	return (clipb.history);
}
