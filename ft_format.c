/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 19:57:30 by aholster       #+#    #+#                */
/*   Updated: 2019/06/01 15:09:56 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_judex(unsigned char *start, size_t *index, t_print *clipb)
{
	size_t	judex;

	judex = 0;
	while (start[judex] != '\0' && start[judex] != '%')
	{
		judex++;
	}
	if (clipb->printer(start, judex, clipb) == -1)
		return (-1);
	*index += judex;
	return (1);
}

static int	ft_charskip(unsigned char *c)
{
	if (c[0] == '\0')
		return (0);
	if ((c[0] & 128) == 0)
		return (1);
	else if (c[0] >= 240 && c[0] <= 247)
		return (4);
	else if (c[0] >= 224 && c[0] <= 239)
		return (3);
	else if (c[0] >= 192 && c[0] <= 223)
		return (2);
	return (1);
}

static size_t	ft_percent_printer(unsigned char* format, t_print *clipb)
{
	unsigned char	*str;
	size_t			index;
	size_t			length;

	index = 0;
	length = 0;
	while (format[index] == '%')
	{
		length++;
		index++;
	}
	length /= 2;
	if ((length % 2) == 0)
		return (-1); // !error! -> data argument won't be used then. (how do we handle?)
	str = (unsigned char*)ft_stralloc(length, '%');
	clipb->printer(str, length, clipb);
	return (index);
}

int			ft_format(va_list ap, unsigned char *format, t_print *clipb)
{
	size_t		index;
	t_flag		flags;
	t_writer	functbl[FUNCSIZE];

	index = 0;
	ft_flinit(clipb, &flags);
	ft_functblinit(functbl);
	while (format[index] != '\0')
	{
		if (format[index] == '%')
		{
			if (format[index + 1] == '%')
				index += ft_percent_printer(&format[index + 1], clipb);
			index += ft_flagharvest(&format[index + 1], clipb);
			if (ft_dispatcher(ap, &format[index], functbl, clipb) == -1)
				return (-1);
			index += ft_charskip(&format[index]);
		}
		else if (ft_judex(&format[index], &index, clipb) == -1)
			return (-1);
	}
	return (1);
}
