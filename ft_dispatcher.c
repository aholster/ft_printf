/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dispatcher.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:00:54 by aholster       #+#    #+#                */
/*   Updated: 2019/09/13 18:20:57 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	ft_operator(char conversion)
{
	if (conversion >= 'A' && conversion <= 'z')
		return (conversion - 'A');
	return (-1);
}

static int	ft_exception(const char *restrict specifier, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1)
	{
		if (flagverif('0', clipb->flags) == 1)
		{
			if (ft_zero_padder(1, clipb) == -1)
				return (-1);
		}
		else if (ft_space_padder(1, clipb) == -1)
			return (-1);
	}
	if (clipb->printer(specifier, 1, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1)
	{
		if (flagverif('0', clipb->flags) == 1)
		{
			if (ft_zero_padder(1, clipb) == -1)
				return (-1);
		}
		else if (ft_space_padder(1, clipb) == -1)
			return (-1);
	}
	return (1);
}

int			ft_dispatcher(const char *restrict specifier,\
				t_writer *functbl, t_print *clipb)
{
	int				index;

	index = ft_operator(specifier[0]);
	if (index == -1 || functbl[index] == NULL)
	{
		if (specifier[0] == '%')
			if (ft_exception(&specifier[0], clipb) == -1)
				return (-1);
	}
	else
	{
		if ((functbl[index])(clipb->args, clipb) == -1)
			return (-1);
	}
	return (1);
}
