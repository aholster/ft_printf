/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_arg_extract.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 21:32:51 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 10:29:52 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag_parser.h"
#include <limits.h>

void	ft_flag_arg_extract(const char *const format,\
			size_t *const aindex,\
			t_writer *const clipb)
{
	t_flag *const	flags = clipb->flags;
	int				num;

	(void)format;
	num = va_arg(clipb->args, int);
	if (num < 0)
	{
		flags->padding = ((-num) & UINT_MAX);
		ft_turn_on_flag('-', flags);
	}
	else
	{
		flags->padding = num;
	}
	*aindex += 1;
}
