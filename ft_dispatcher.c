/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dispatcher.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:00:54 by aholster       #+#    #+#                */
/*   Updated: 2019/04/22 21:46:18 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_operator(char conversion)
{
	if (ft_iscapital(conversion) == 1)
		return (conversion - 'A');
	else if (ft_islowercase(conversion) == 1)
		return (conversion - ('a' + 6));
	else
		return (52);
}

int			ft_dispatcher(va_list ap, char *specifier, void *functbl[53],\
			t_print *clipb)
{
	int		index;
	int		(*basic)(va_list, t_print*);
	int		(*exception)(int, va_list, t_print*);

	index = ft_operator(specifier[0]);
	if (index >= 52 || functbl[index] == 0)
	{
		exception = functbl[52];
		if (exception((int)(specifier[0]), ap, clipb) == -1)
			return (-1);
	}
	else
	{
		basic = functbl[index];
		if (basic(ap, clipb) == -1)
			return (-1);
	}
	return (1);
}
