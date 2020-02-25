/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 19:57:30 by aholster       #+#    #+#                */
/*   Updated: 2020/02/25 10:56:12 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/ft_internals.h"

static int		ft_judex(const char *format,\
					size_t *const index,\
					const size_t len,\
					t_writer *const clipb)
{
	size_t		judex;

	judex = *index;
	while (judex < len && format[judex] != '%')
	{
		judex++;
	}
	if (clipb->self(format + *index, judex - *index, clipb) == -1)
		return (-1);
	*index = judex;
	return (1);
}

/*
**	possibly add W_char or utf8 support for charskip
*/

int				ft_format(const char *format,\
						t_writer *const clipb)
{
	size_t				index;
	size_t				len;
	t_flag				flags;

	index = 0;
	len = ft_strlen(format);
	clipb->flags = &flags;
	while (index < len)
	{
		if (format[index] == '%')
		{
			index++;
			ft_flagharvest(format, &index, clipb);
			if (ft_dispatcher(format[index], clipb) == -1)
				return (-1);
			if (format[index] != '\0')
			{
				index++;
			}
		}
		else if (ft_judex(format, &index, len, clipb) == -1)
			return (-1);
	}
	return (1);
}
