/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_n.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/11 19:04:14 by aholster       #+#    #+#                */
/*   Updated: 2019/06/11 19:24:05 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_n(va_list ap, t_print *clipb)
{
	size_t	history;
	t_flag	*flags;
	t_nptrs	ptr;

	history = clipb->history + clipb->current;
	flags = clipb->flags;
	if (doubleverif('h', flags) == 1)
	{
		ptr.hh = (char *)va_arg(ap, int *);
		*ptr.hh = (char)history;
	}
	else if (flagverif('h', flags) == 1)
	{
		ptr.h = (short *)va_arg(ap, int *);
		*ptr.h = (short)history;
	}
	else if (flagverif('l', flags) == 1)
	{
		ptr.l = (long *)va_arg(ap, long *);
		*ptr.l = (long)history;
	}
	else if (doubleverif('l', flags) == 1)
	{
		ptr.ll = (long long *)va_arg(ap, long long *);
		*ptr.ll = (long long)history;
	}
	else
	{
		ptr.i = va_arg(ap, int *);
		*ptr.i = (int)history;
	}
	return (1);
}
