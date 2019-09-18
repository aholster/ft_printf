/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vsnprintf.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 15:19:36 by aholster       #+#    #+#                */
/*   Updated: 2019/09/18 20:24:57 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static int	ft_write_to_str(const char *restrict mem, size_t size, t_writer *const restrict clipb)
{
	size_t	block;

	
	return (1);
}

static void	ft_vsn_clipb_init(va_list args, char *str,t_wrt_ptr printer, t_writer *const restrict clipb)
{
	clipb->alst = NULL;
	va_copy(clipb->args, args);
	clipb->history = 0;
	clipb->current = 0;
	clipb->fd = -1;
	clipb->self = printer;
	clipb->buffer = str;
}

int			ft_vsnprintf(char *str, size_t size, const char *restrict format, va_list args)
{
t_writer	clipb;

	if (size == 0)
		return (0);
	ft_vsn_clipb_init(args, str, ft_write_to_str, &clipb);

	return (clipb.history);
}
