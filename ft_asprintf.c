/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_asprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 19:47:52 by aholster       #+#    #+#                */
/*   Updated: 2019/06/20 14:10:42 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_lstcreator(const unsigned char *mem, const size_t size,\
							t_print *clipb)
{
	t_list	*cur;

	cur = ft_lstnew(mem, size);
	if (cur == NULL)
		return (-1);
	ft_lstaddend(clipb->alst, cur);
	clipb->history += clipb->current;
	clipb->current = 0;
	return (0);
}

static int	ft_lstbufmanager(const unsigned char *mem, size_t size,\
								t_print *clipb)
{
	size_t	block;

	if (mem == NULL)
	{
		if (ft_lstcreator((const unsigned char *)clipb->buffer, \
				clipb->current, clipb) == -1)
			return (-1);
	}
	else
		while (size > 0)
		{
			if (clipb->current == BUFFSIZE)
				if (ft_lstcreator((const unsigned char *)clipb->buffer, \
						BUFFSIZE, clipb) == -1)
					return (-1);
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

static int	ft_as_clipb_init(va_list args, t_list **alst, \
							t_wrt_ptr printer, t_print *clipb)
{
	clipb->alst = alst;
	va_copy(clipb->origin_args, args);
	va_copy(clipb->args, args);
	clipb->history = 0;
	clipb->current = 0;
	clipb->fd = -1;
	clipb->printer = printer;
	clipb->buffer = (char *)malloc(sizeof(char) * BUFFSIZE);
	if (clipb->buffer == NULL)
		return (-1);
	return (1);
}

int			ft_asprintf(char **ret, const char *format, ...)
{
	va_list		args;
	t_print		clipb;
	t_list		*buflst;

	buflst = NULL;
	va_start(args, format);
	if (ft_as_clipb_init(args, &buflst, ft_lstbufmanager, &clipb) == -1)
		return (-1);
	if (ft_format((unsigned char *)format, &clipb) == -1)
	{
		free(clipb.buffer);
		return (-1);
	}
	if (ft_lstbufmanager(NULL, 0, &clipb) == -1)
		return (-1);
	if (ft_lstmemtomem(ret, NULL, buflst) == -1)
		return (-1);
	ft_lstdel(&buflst, ft_del);
	free(clipb.buffer);
	va_end(args);
	va_end(clipb.origin_args);
	va_end(clipb.args);
	return (clipb.history);
}
