/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vasprintf.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 15:19:40 by aholster       #+#    #+#                */
/*   Updated: 2019/09/25 14:38:57 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static int	ft_lstcreator(const char *restrict mem, const size_t size,\
			t_writer *const restrict clipb, t_as_write *const restrict info)
{
	t_list	*cur;

	cur = ft_lstnew(mem, size);
	if (cur == NULL)
		return (-1);
	ft_lstaddend(info->alst, cur);
	clipb->history += clipb->current;
	clipb->current = 0;
	return (0);
}

static int	ft_lst_bufmanager(const char *restrict mem, size_t size,\
							t_writer *const restrict clipb)
{
	size_t		block;
	t_as_write	*info;

	info = clipb->info.as;
	if (mem == NULL)
	{
		if (ft_lstcreator(info->buffer, clipb->current, clipb, info) == -1)
			return (-1);
	}
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
				if (ft_lstcreator(info->buffer, BUFFSIZE, clipb, info) == -1)
					return (-1);
		}
	return (0);
}

static int	ft_vas_clipb_init(va_list args, t_list **alst, \
						t_wrt_ptr printer, t_writer *const restrict clipb)
{
	t_as_write	*info;

	info = clipb->info.as;
	va_copy(clipb->args, args);
	clipb->history = 0;
	clipb->current = 0;
	clipb->self = printer;
	info->alst = alst;
	return (1);
}

int			ft_vasprintf(char **ret, const char *restrict format, va_list args)
{
	t_writer	clipb;
	t_as_write	info;
	t_list		*lst;

	clipb.info.as = &info;
	lst = NULL;
	if (ft_vas_clipb_init(args, &lst, ft_lst_bufmanager, &clipb) == -1)
		return (-1);
	if (ft_format(format, &clipb) == -1)
	{
		ft_lstdel(info.alst, &ft_del);
		return (-1);
	}
	if (ft_lst_bufmanager(NULL, 0, &clipb) == -1)
	{
		ft_lstdel(info.alst, &ft_del);
		return (-1);
	}
	if (ft_lstmemtomem(ret, NULL, lst) == -1)
	{
		ft_lstdel(info.alst, &ft_del);
		return (-1);
	}
	ft_lstdel(&lst, ft_del);
	va_copy(args, clipb.args);
	va_end(clipb.args);
	return (clipb.history);
}
