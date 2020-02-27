/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 19:57:30 by aholster       #+#    #+#                */
/*   Updated: 2020/02/25 18:20:55 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/ft_internals.h"

int				ft_write_wrap(const char *const format,
					const size_t len,
					struct s_writer *const clipb)
{
	if (clipb->err == 0)
	{
		if (clipb->self(format, len, clipb))
		{
			clipb->err = 1;
		}
		else
		{
			return (0);
		}
	}
	return (-1);
}

static void		ft_judex(const char *format,\
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
	ft_write_wrap(format + *index, judex - *index, clipb);
	*index = judex;
}

/*
**	possibly add W_char or utf8 support for charskip
*/

void			ft_format(const char *format,\
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
			ft_dispatcher(format[index], clipb);
			if (format[index] != '\0')
			{
				index++;
			}
		}
		else
		{
			ft_judex(format, &index, len, clipb);
		}
	}
}
