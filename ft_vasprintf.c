/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vasprintf.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 15:19:40 by aholster       #+#    #+#                */
/*   Updated: 2019/09/17 21:07:00 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_lstcreator(const char *restrict mem, const size_t size,\
							t_print *const restrict clipb)
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

static int	ft_lst_bufmanager(const char *restrict mem, size_t size,\
								t_print *const restrict clipb)
{
	size_t	block;

	if (mem == NULL)
	{
		if (ft_lstcreator(clipb->buffer, clipb->current, clipb) == -1)
			return (-1);
	}
	else
		while (size > 0)
		{
			if (clipb->current == BUFFSIZE)
				if (ft_lstcreator(clipb->buffer, BUFFSIZE, clipb) == -1)
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

static int	ft_vas_clipb_init(va_list args, t_list **alst, \
							t_wrt_ptr printer, t_print *const restrict clipb)
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

int			ft_vasprintf(char **ret, const char *restrict format, va_list args)
{
	t_print		clipb;
	t_list		*buflst;

	buflst = NULL;
	if (ft_vas_clipb_init(args, &buflst, ft_lst_bufmanager, &clipb) == -1)
		return (-1);
	if (ft_format(format, &clipb) == -1)
	{
		free(clipb.buffer);
		ft_lstdel(clipb.alst, &ft_del);
		return (-1);
	}
	if (ft_lst_bufmanager(NULL, 0, &clipb) == -1)
	{
		free(clipb.buffer);
		ft_lstdel(clipb.alst, &ft_del);
		return (-1);
	}
	if (ft_lstmemtomem(ret, NULL, buflst) == -1)
	{
		free(clipb.buffer);
		ft_lstdel(clipb.alst, &ft_del);
		return (-1);
	}
	ft_lstdel(&buflst, ft_del);
	free(clipb.buffer);
	va_copy(args, clipb.args);
	va_end(clipb.origin_args);
	va_end(clipb.args);
	return (clipb.history);
}
