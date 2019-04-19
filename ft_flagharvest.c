/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flagharvest.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:22:09 by aholster       #+#    #+#                */
/*   Updated: 2019/04/19 12:54:33 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_valiflag(unsigned char *seg, t_flag *flags)
{
	if (seg >= 128 || seg == '\0')
		return (-1);
	else if (seg[0] == seg[1])
	{
		if (seg[0] >= 64 &&\
			((1LLU << (seg[0] - 64)) & (*flags).doubleflags[1] == 1)) //corrected
			return (1);
		else if ((1LLU << seg[0]) & (*flags).doubleflags[0] == 1) //corrected
			return (1);
	}
	else if (seg[0] >= 64 &&\
			(1LLU << (seg[0] - 64)) & (*flags).standflags[1] == 1) //corrected
		return (1);
	else if (((1LLU << seg[0]) & (*flags).standflags[0]) == 1) //corrected
		return (1);
	return (-1);
}

static void	ft_flagreset(t_flag *flags) //corrected
{
	(*flags).actiflags[0] = 0;
	(*flags).actiflags[1] = 0;
	(*flags).precision = 0;
	(*flags).spadding = 0;
	(*flags).npadding = 0;
}

int			ft_flagharvest(char *format, t_flag *flags)
{
	size_t	index;

	index = 0;
	ft_flagreset(flags);
	while (ft_valiflag(&format[index], flags) == 1)
	{
		//for doubleflags, increment index another step to avoid valiflag bugging
		//if (&format[index] == &format[index + 1] && ft_validflag(&format[index + 1], flags) == 1)
		//	index++;
		index++;
	}
	return (index);
}
