/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_n.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/11 19:04:14 by aholster       #+#    #+#                */
/*   Updated: 2019/09/18 18:30:35 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static int	ft_double_flags(va_list args, size_t history, t_flag *flags)
{
	t_nptrs ptr;

	if (doubleverif('h', flags) == 1)
	{
		ptr.hh = (char *)va_arg(args, int *);
		*ptr.hh = (char)history;
		return (1);
	}
	if (doubleverif('l', flags) == 1)
	{
		ptr.ll = (long long *)va_arg(args, long long *);
		*ptr.ll = (long long)history;
		return (1);
	}
	return (-1);
}

static int	ft_single_flags(va_list args, size_t history, t_flag *flags)
{
	t_nptrs ptr;

	if (flagverif('h', flags) == 1)
	{
		ptr.h = (short *)va_arg(args, int *);
		*ptr.h = (short)history;
		return (1);
	}
	if (flagverif('l', flags) == 1)
	{
		ptr.l = (long *)va_arg(args, long *);
		*ptr.l = (long)history;
		return (1);
	}
	return (-1);
}

int			ft_n(va_list args, t_print *const restrict clipb)
{
	size_t	history;
	t_flag	*flags;
	t_nptrs	ptr;

	history = clipb->history + clipb->current;
	flags = clipb->flags;
	if (ft_single_flags(args, history, flags) == 1)
		return (1);
	if (ft_double_flags(args, history, flags) == 1)
		return (1);
	else
	{
		ptr.i = va_arg(args, int *);
		*ptr.i = (int)history;
	}
	return (1);
}
