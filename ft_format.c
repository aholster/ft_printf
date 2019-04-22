/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 19:57:30 by aholster       #+#    #+#                */
/*   Updated: 2019/04/22 22:11:16 by aholster      ########   odam.nl         */
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

int			ft_format(va_list ap, char *format, t_print *clipb)
{
	size_t		index;
	t_flag		flags;
	void		*functbl[53];

	index = 0;
	ft_flinit(clipb, &flags);
	while (format[index] != '\0')
	{
		if (format[index] == '%')
		{
			index += ft_flagharvest((unsigned char*)&format[index], clipb);
			if (ft_dispatcher(ap, &format[index], functbl, clipb) == -1)
				return (-1);
		}
		else if (ft_judex(&format[index], &index, clipb) == -1)
			return (-1);
		index++;
	}
	return (1);
}
