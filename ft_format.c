/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 19:57:30 by aholster       #+#    #+#                */
/*   Updated: 2019/09/16 21:31:00 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_judex(const char *restrict format, size_t *index,\
				const size_t len, t_print *const clipb)
{
	size_t	judex;

	judex = *index;
	while (judex < len && format[judex] != '%')
	{
		judex++;
	}
	if (clipb->printer(format + *index, judex - *index, clipb) == -1)
		return (-1);
	*index = judex;
	return (1);
}

static int		ft_charskip(const char *c)
{
	if (c[0] == '\0')
		return (0);
	// if ((c[0] & 128) == 0)
	// 	return (1);
	// else if (c[0] >= 240 && c[0] <= 247)
	// 	return (4);
	// else if (c[0] >= 224 && c[0] <= 239)
	// 	return (3);
	// else if (c[0] >= 192 && c[0] <= 223)
	// 	return (2);
	return (1);
}

int				ft_format(const char *restrict format, t_print *const clipb)
{
	size_t		index;
	size_t		len;
	t_flag		flags;
	t_writer	functbl[FUNCSIZE];

	index = 0;
	len = ft_strlen(format);
	ft_flinit(clipb, &flags);
	ft_functblinit(functbl);
	while (index < len)
	{
		if (format[index] == '%')
		{
			index++;
			ft_flagharvest(format, &index, clipb);
			if (ft_dispatcher(&format[index], functbl, clipb) == -1)
				return (-1);
			index += ft_charskip(format + index);
		}
		else if (ft_judex(format, &index, len, clipb) == -1)
			return (-1);
	}
	return (1);
}
