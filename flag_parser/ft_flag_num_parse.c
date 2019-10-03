/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_num_parse.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 21:31:43 by aholster       #+#    #+#                */
/*   Updated: 2019/10/03 22:30:20 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag_parser.h"

static int	ft_isdigit_internal(const char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void		ft_flag_num_parse(const char *const restrict format,\
				size_t *const restrict aindex,\
				t_writer *const restrict clipb)
{
	size_t					subdex;
	unsigned int			num;
	t_flag *const restrict	flags = clipb->flags;

	subdex = *aindex;
	num = 0;
	while (ft_isdigit_internal(format[subdex]) == 1)
	{
		num += (format[subdex] - '0');
		if (ft_isdigit_internal(format[subdex + 1]) == 1)
			num *= 10;
		subdex++;
	}
	flags->padding = num;
	*aindex = subdex;
}
