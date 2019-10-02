/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vsnprintf.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 15:19:36 by aholster       #+#    #+#                */
/*   Updated: 2019/10/02 17:34:32 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static int	ft_write_to_str(const char *restrict mem, size_t size,\
						t_writer *const restrict clipb)
{
	t_sn_write const *const restrict	info = clipb->info.sn;
	const size_t						capacity = info->capacity;
	size_t								free_space;

	if (clipb->history < capacity)
	{
		free_space = capacity - clipb->history;
		if (size > free_space)
		{
			ft_memcpy(info->str + clipb->history, mem, free_space);
			info->str[capacity - 1] = '\0';
		}
		else
		{
			ft_memcpy(info->str + clipb->history, mem, size);
			info->str[clipb->history + size] = '\0';
		}
		clipb->history += size;
	}
	else
		clipb->history += size;
	return (1);
}

static void	ft_vsn_clipb_init(va_list args, t_wrt_ptr printer,\
								t_writer *const restrict clipb)
{
	va_copy(clipb->args, args);
	clipb->history = 0;
	clipb->current = 0;
	clipb->self = printer;
}

int			ft_vsnprintf(char *str, size_t size, const char *restrict format,\
						va_list args)
{
	t_writer	clipb;
	t_sn_write	info;

	clipb.info.sn = &info;
	if (size == 0)
		return (0);
	info.str = str;
	info.capacity = size;
	ft_vsn_clipb_init(args, ft_write_to_str, &clipb);
	if (ft_format(format, &clipb) == -1)
	{
		return (-1);
	}
	va_copy(args, clipb.args);
	va_end(clipb.args);
	return (clipb.history);
}
