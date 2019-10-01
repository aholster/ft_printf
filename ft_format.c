/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 19:57:30 by aholster       #+#    #+#                */
/*   Updated: 2019/10/01 19:07:22 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/ft_internals.h"

static int		ft_judex(const char *restrict format, size_t *index,\
				const size_t len, t_writer *const restrict clipb)
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

static int		ft_charskip(const char *c)
{
	if (c[0] == '\0')
		return (0);
	return (1);
}

/*
**	possibly add W_char or utf8 support for charskip
*/

int				ft_format(const char *restrict format,\
						t_writer *const restrict clipb)
{
	size_t				index;
	size_t				len;
	t_flag				flags;

	index = 0;
	len = ft_strlen(format);
	ft_flinit(clipb, &flags);
	while (index < len)
	{
		if (format[index] == '%')
		{
			index++;
			ft_flagharvest(format, &index, clipb);
			if (ft_dispatcher(&format[index], clipb) == -1)
				return (-1);
			index += ft_charskip(format + index);
		}
		else if (ft_judex(format, &index, len, clipb) == -1)
			return (-1);
	}
	return (1);
}
