/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flinit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:44:14 by aholster       #+#    #+#                */
/*   Updated: 2019/06/07 14:49:03 by jesmith       ########   odam.nl         */
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
			(*flags).statiflags[1] |= (1LLU << (VALFLG[index] - 64));
		else
			(*flags).statiflags[0] |= (1LLU << VALFLG[index]);
		index++;
	}
}

static void	ft_dblflg(t_flag *flags)
{
	size_t	index;

	index = 0;
	while (DBLFLG[index] != '\0')
	{
		if (DBLFLG[index] >= 64)
			(*flags).statidoubles[1] |= (1LLU << (DBLFLG[index] - 64));
		else
			(*flags).statidoubles[0] |= (1LLU << DBLFLG[index]);
		index++;
	}
}

void		ft_flinit(t_print *clipb, t_flag *flags)
{
	(*clipb).flags = flags;
	(*flags).statiflags[0] = 0;
	(*flags).statiflags[1] = 0;
	(*flags).statidoubles[0] = 0;
	(*flags).statidoubles[1] = 0;
	ft_dblflg(flags);
	ft_valflg(flags);
}
