/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dispatcher.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:00:54 by aholster       #+#    #+#                */
/*   Updated: 2019/06/19 16:28:19 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


static int	ft_operator(char conversion)
{
	if (conversion >= 'A' && conversion <= 'z')
		return (conversion - 'A');
	return (-1);
}

// static int	ft_expection(unsigned char *specifer, va_list args, t_print clipb)
// {
// 	int	index;

// 	index = 0;
// 	if (specifer[index] == '%')
// 	{
// 		if (clipb->printer(specifer, 1, clipb) == -1)
// 			return (-1);
// 	}
// 	return (1);
// }

int			ft_dispatcher(const unsigned char *specifier,\
				t_writer *functbl, t_print *clipb)
{
	// int				index;
	// va_list			args;

	// va_copy(clipb->args, args);
	index = ft_operator(specifier[0]);
	if (index == -1 || functbl[index] == NULL)
	{
		// if (ft_excpetion(int)(specifer[0]), args, clipb) == -1)
		// 	return (-1);
	}
	else
	{
		if ((functbl[index])(clipb->args, clipb) == -1)
			return (-1);
	}
	return (1);
}
