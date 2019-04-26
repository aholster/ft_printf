/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dispatcher.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:00:54 by aholster       #+#    #+#                */
/*   Updated: 2019/04/26 19:08:03 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_operator(char conversion)
{

	if (ft_iscapital(conversion) == 1)
		return (conversion - 'A');
	else if (ft_islowercase(conversion) == 1)
		return (conversion - ('A' + 6));
	return (-1);
}

int			ft_dispatcher(va_list ap, unsigned char *specifier, void **functbl,\
			t_print *clipb)
{
	int		index;
	int		(*basic)(va_list, t_print*);

	index = ft_operator(specifier[0]);
	if (index == -1 || functbl[index] == NULL)
	{
		// if (exception((int)(specifier[0]), ap, clipb) == -1)
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
