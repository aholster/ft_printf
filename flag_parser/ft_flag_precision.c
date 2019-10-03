/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_precision.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 21:32:49 by aholster       #+#    #+#                */
/*   Updated: 2019/10/03 22:27:40 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag_parser.h"
#include <limits.h>

static int		ft_isdigit_internal(const char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static size_t	precision_num_parse(const char *const restrict format,\
					t_flag *const restrict flags)
{
	size_t					index;
	unsigned int			num;

	num = 0;
	index = 0;
	while (ft_isdigit_internal(format[index]) == 1)
	{
		num += (format[index] - '0');
		if (ft_isdigit_internal(format[index + 1]) == 1)
			num *= 10;
		index++;
	}
	flags->padding = num;
	return (index);
}

static void		precision_arg_extract(va_list args,\
					t_flag *const restrict flags)
{
	int						num;

	num = va_arg(args, int);
	if (num < 0)
	{
		flags->padding = ((-num) & UINT_MAX);
	}
	else
	{
		flags->padding = num;
	}
}

void			ft_flag_precision(const char *const restrict format,\
					size_t *const restrict aindex,\
					t_writer *const restrict clipb)
{
	t_flag *const restrict	flags = clipb->flags;
	size_t					subdex;

	subdex = (*aindex) + 1;
	ft_turn_on_flag('.', flags);
	if (format[subdex] == '*')
	{
		precision_arg_extract(clipb->args, flags);
		subdex++;
	}
	else if (format[subdex] >= '1' && format[subdex] <= '9')
	{
		subdex += precision_num_parse(format, flags);
	}
	*aindex = subdex;
}
