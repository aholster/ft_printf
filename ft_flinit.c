/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flinit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:44:14 by aholster       #+#    #+#                */
/*   Updated: 2019/04/18 18:56:11 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_valflg(t_flag *flags)
{
	size_t	index;

	index = 0;
	while (VALFLG[index] != '\0')
	{
		if (VALFLG[index] >= 64)
			flags.standflags[1] |= (1LLU << (VALFLG[index] - 64));
		else
			flags.standflags[0] |= (1LLU << VALFLG[index]);
		index++;
	}
}

static void	ft_dblflg(t_flag *flags)
{
	size_t	index;

	index = 0;
	while (DBLFLG[index] != '\0')
	{
		if (DBLFLGindex] >= 64)
			flags.standflags[1] |= (1LLU << (DBLFLG[index] - 64));
		else
			flags.standflags[0] |= (1LLU << DBLFLG[index]);
		index++;
	}
}

void	ft_flinit(va_list ap, t_flag *flags)
{
	(*flags).ap = ap;
	flags.standflags[0] = 0;
	flags.standflags[1] = 0;
	flags.doubleflags[0] = 0;
	flags.doubleflags[1] = 0;
	ft_dblflg(flags);
	ft_valflg(flags);
}
