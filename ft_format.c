/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 19:57:30 by aholster       #+#    #+#                */
/*   Updated: 2019/04/24 16:35:16 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_judex(char *start, size_t *index, t_print *clipb)
{
	size_t	judex;

	judex = 0;
	while (start[judex] != '\0' && start[judex] != '%')
	{
		judex++;
	}
	if ((*clipb).printer(start, judex - 1, clipb) == -1)
		return (-1);
	*index += judex - 1;
	return (1);
}

static int	ft_charskip(unsigned char *c)
{
	if (c[0] & 128 == 0)// <= 127
		return (1);
	else if (c[0] >= 240 && c[0] <= 247)// <= 247
		return (4);
	else if (c[0] >= 224 && c[0] <= 239)// <= 239
		return (3);
	else if (c[0] >= 192 && c[0] <= 223)// <= 223
		return (2);
	return (1);
}

int			ft_format(va_list ap, unsigned char *format, t_print *clipb)
{
	size_t		index;
	t_flag		flags;
	void		*functbl[FUNCSIZE];

	index = 0;
	ft_flinit(clipb, &flags);
	while (format[index] != '\0')
	{
		if (format[index] == '%')
		{
			index += ft_flagharvest(&format[index], clipb);
			if (ft_dispatcher(ap, &format[index], &functbl, clipb) == -1)
				return (-1);
		}
		else if (ft_judex(&format[index], &index, clipb) == -1)
			return (-1);
		index += ft_charskip(&format[index]);
	}
	return (1);
}
