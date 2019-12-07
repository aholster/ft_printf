/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vasprintf.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 15:19:40 by aholster       #+#    #+#                */
/*   Updated: 2019/12/07 04:28:50 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static int	fvect_upscale(t_writer *const restrict clipb)
{
	char			*new_vect;
	const size_t	new_size = clipb->info.as->current_size * 2;

	new_vect = malloc(new_size + 1);
	if (new_vect == NULL)
	{
		return (-1);
	}
	else
	{
		ft_bzero(new_vect, new_size + 1);
		ft_memcpy(new_vect, clipb->info.as->str_vect, clipb->history + 1);
		free(clipb->info.as->str_vect);
		clipb->info.as->str_vect = new_vect;
		clipb->info.as->current_size = new_size;
		return (1);
	}
}

static int	ft_lst_bufmanager(const char *restrict mem, size_t size,\
							t_writer *const restrict clipb)
{
	if (size + clipb->history + 1 > clipb->info.as->current_size)
	{
		if (fvect_upscale(clipb) == -1)
		{
			return (-1);
		}
	}
	ft_memcpy(clipb->info.as->str_vect + clipb->history, mem, size);
	clipb->history += size;
	clipb->info.as->str_vect[clipb->history] = '\0';
	return (1);
}

static int	ft_vas_clipb_init(va_list args,\
				t_wrt_ptr printer,\
				t_writer *const restrict clipb)
{
	t_as_write	*const info = clipb->info.as;

	info->str_vect = malloc(sizeof(char) * BUFFSIZE + 1);
	if (info->str_vect == NULL)
	{
		return (-1);
	}
	else
	{
		ft_bzero(info->str_vect, BUFFSIZE + 1);
		info->current_size = BUFFSIZE;
		va_copy(clipb->args, args);
		clipb->history = 0;
		clipb->current = 0;
		clipb->self = printer;
		return (1);
	}
}

int			ft_vasprintf(char **ret, const char *restrict format, va_list args)
{
	t_writer	clipb;
	t_as_write	info;

	ft_bzero(&info, sizeof(t_as_write));
	clipb.info.as = &info;
	if (ft_vas_clipb_init(args, ft_lst_bufmanager, &clipb) == -1)
	{
		free(info.str_vect);
		return (-1);
	}
	if (ft_format(format, &clipb) == -1)
	{
		free(info.str_vect);
		return (-1);
	}
	*ret = ft_memdup(info.str_vect, clipb.history + 1);
	free(info.str_vect);
	if (*ret == NULL)
	{
		return (-1);
	}
	va_copy(args, clipb.args);
	va_end(clipb.args);
	return (clipb.history);
}
