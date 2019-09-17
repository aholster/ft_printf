/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dispatcher.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:00:54 by aholster       #+#    #+#                */
/*   Updated: 2019/09/17 21:07:00 by aholster      ########   odam.nl         */
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

static int	ft_conversion_exception(const char *const restrict specifier,\
									t_print *const restrict clipb)
{
	int				zeroflag;
	int				padf;
	const size_t	len = 1; //upgrade DISSSS maybe?

	zeroflag = flagverif('0', clipb->flags);
	if (flagverif('-', clipb->flags) == -1)
	{
		if (zeroflag == 1)
			padf = ft_zero_padder(len, clipb);
		else
			padf = ft_space_padder(len, clipb);
		if (padf == -1 || clipb->printer(specifier, len, clipb) == -1)
			return (-1);
	}
	else
	{
		if (clipb->printer(specifier, len, clipb) == -1)
			return (-1);
		padf = ft_space_padder(len, clipb);
		if (padf == -1)
			return (-1);
	}
	return (1);
}

int			ft_dispatcher(const char *restrict specifier,\
				t_writer *functbl, t_print *const restrict clipb)
{
	int				index;

	index = ft_operator(specifier[0]);
	if (index == -1 || functbl[index] == NULL)
	{
		if (specifier[0] == '\0')
			return (1);
		else
		{
			if (ft_conversion_exception(&specifier[0], clipb) == -1)
				return (-1);
		}
	}
	else
	{
		if ((functbl[index])(clipb->args, clipb) == -1)
			return (-1);
	}
	return (1);
}
