/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dispatcher.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:00:54 by aholster       #+#    #+#                */
/*   Updated: 2019/05/19 16:20:35 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_operator(char conversion)
{
	if (conversion >= 'A' && conversion <= 'Z')
		return (conversion - 'A');
	return (-1);
}

int			ft_dispatcher(va_list ap, unsigned char *specifier,\
				t_writer *functbl, t_print *clipb)
{
	int		index;

	index = ft_operator(specifier[0]);
	if (index == -1 || functbl[index] == NULL)
	{
		// if (exception((int)(specifier[0]), ap, clipb) == -1)
			return (-1);
	}
	else
	{
		if ((functbl[index])(ap, clipb) == -1)
			return (-1);
	}
	return (1);
}
