/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:14 by aholster       #+#    #+#                */
/*   Updated: 2019/06/05 17:02:36 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_bufmanager(const unsigned char *mem, size_t size, t_print *clipb)
{
	size_t	block;

	if (mem == NULL)
	{
		write(clipb->fd, clipb->buffer, clipb->current);
		clipb->history += clipb->current;
		clipb->current = 0;
		return (0);
	}
	while (size > 0)
	{
		if (clipb->current == BUFFSIZE)
		{
			write(clipb->fd, clipb->buffer, BUFFSIZE);
			clipb->history += clipb->current;
			clipb->current = 0;
		}
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

int		ft_printf(char *format, ...)
{
	va_list 	ap;
	t_print 	clipb;

	va_start(ap, format);
	if (ft_clinit(NULL, 1, ft_bufmanager, &clipb) == -1)
		return (-1);
	if (ft_format(ap, (unsigned char *)format, &clipb) == -1)
	{
		free(clipb.buffer);
		return (-1);
	}
	ft_bufmanager(NULL, 0, &clipb);
	va_end(ap);
	return (clipb.history);
}
