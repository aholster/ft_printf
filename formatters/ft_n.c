/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_n.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/11 19:04:14 by aholster       #+#    #+#                */
/*   Updated: 2020/02/27 13:38:16 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int	ft_double_flags(va_list args,\
				const size_t history,\
				const t_flag *const flags)
{
	t_nptrs ptr;

	if (flgdbl_verif('h', flags) == 1)
	{
		ptr.hh = (char *)va_arg(args, int *);
		*ptr.hh = (char)history;
		return (1);
	}
	if (flgdbl_verif('l', flags) == 1)
	{
		ptr.ll = (long long *)va_arg(args, long long *);
		*ptr.ll = (long long)history;
		return (1);
	}
	return (0);
}

static int	ft_single_flags(va_list args,\
				const size_t history,\
				const t_flag *const flags)
{
	t_nptrs ptr;

	if (flg_verif('h', flags) == 1)
	{
		ptr.h = (short *)va_arg(args, int *);
		*ptr.h = (short)history;
		return (1);
	}
	if (flg_verif('l', flags) == 1)
	{
		ptr.l = (long *)va_arg(args, long *);
		*ptr.l = (long)history;
		return (1);
	}
	return (0);
}

int			ft_n(va_list args, t_writer *const clipb)
{
	const size_t		history = clipb->history + clipb->current;
	const t_flag *const	flags = clipb->flags;
	t_nptrs				ptr;

	if (ft_single_flags(args, history, flags) == 1)
		return (0);
	else if (ft_double_flags(args, history, flags) == 1)
		return (0);
	else
	{
		ptr.i = va_arg(args, int *);
		*ptr.i = (int)history;
	}
	return (0);
}
