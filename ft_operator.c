/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_operator.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:00:54 by aholster       #+#    #+#                */
/*   Updated: 2019/04/18 19:36:34 by aholster      ########   odam.nl         */
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

int			ft_dispatcher(char *specifier, int functbl[53],\
			t_statbuf *buffer, t_flag *flags)
{
	int		index;
	int 	(*basic)(va_list, t_statbuf, t_flag);
	int 	(*exception)(int, va_list, t_statbuf, t_flag);
	

	index = ft_operator(specifier[0]);
	if (index == 52 || functbl[index] == 0)
	{
		exception = functbl[52];
		if (exception((int)(specifier[0]), (*flags).ap, buffer, flags) == -1)
			return (-1);
	}
	else
	{
		basic = functbl[index];
		if (basic(flags.ap, buffer, flags) == -1)
			return (-1);
	}
	return (1);
}
