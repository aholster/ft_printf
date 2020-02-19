/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_precision.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 21:32:49 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 10:29:57 by aholster      ########   odam.nl         */
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

static void		precision_num_parse(const char *const format,\
					size_t *aindex,\
					t_flag *const flags)
{
	size_t					subdex;
	unsigned int			num;

	num = 0;
	subdex = *aindex;
	while (ft_isdigit_internal(format[subdex]) == 1)
	{
		num += (format[subdex] - '0');
		if (ft_isdigit_internal(format[subdex + 1]) == 1)
			num *= 10;
		subdex++;
	}
	flags->precision = num;
	*aindex = subdex;
}

static void		precision_arg_extract(va_list args,\
					t_flag *const flags)
{
	int						num;

	num = va_arg(args, int);
	if (num >= 0)
	{
		ft_turn_on_flag('.', flags);
		flags->precision = num;
	}
}

void			ft_flag_precision(const char *const format,\
					size_t *const aindex,\
					t_writer *const clipb)
{
	t_flag *const	flags = clipb->flags;
	size_t			subdex;

	subdex = (*aindex) + 1;
	if (format[subdex] == '*')
	{
		precision_arg_extract(clipb->args, flags);
		subdex++;
	}
	else if (format[subdex] >= '0' && format[subdex] <= '9')
	{
		precision_num_parse(format, &subdex, flags);
		ft_turn_on_flag('.', flags);
	}
	else
	{
		flags->precision = 0;
		ft_turn_on_flag('.', flags);
	}
	*aindex = subdex;
}
