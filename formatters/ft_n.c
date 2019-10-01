/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_n.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/11 19:04:14 by aholster       #+#    #+#                */
/*   Updated: 2019/10/01 14:48:52 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static int	ft_double_flags(va_list args, const size_t history,\
							const t_flag *const restrict flags)
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
	return (0);
}

static int	ft_single_flags(va_list args, const size_t history,\
							const t_flag *const restrict flags)
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
	return (0);
}

int			ft_n(va_list args, t_writer *const restrict clipb)
{
	const size_t					history = clipb->history + clipb->current;
	const t_flag *const restrict	flags = clipb->flags;
	t_nptrs							ptr;

	if (ft_single_flags(args, history, flags) == 1)
		return (1);
	else if (ft_double_flags(args, history, flags) == 1)
		return (1);
	else
	{
		ptr.i = va_arg(args, int *);
		*ptr.i = (int)history;
	}
	return (1);
}
