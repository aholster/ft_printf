/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flinit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:44:14 by aholster       #+#    #+#                */
/*   Updated: 2019/09/18 18:25:57 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static void	init_flags(t_flag *flags)
{
	size_t	index;

	index = 0;
	while (VALID_FLG[index] != '\0')
	{
		if (VALID_FLG[index] >= 64)
			(*flags).statiflags[1] |= (1LLU << (VALID_FLG[index] - 64));
		else
			(*flags).statiflags[0] |= (1LLU << VALID_FLG[index]);
		index++;
	}
}

static void	init_dflags(t_flag *flags)
{
	size_t	index;

	index = 0;
	while (VALID_D_FLG[index] != '\0')
	{
		if (VALID_D_FLG[index] >= 64)
			(*flags).statidoubles[1] |= (1LLU << (VALID_D_FLG[index] - 64));
		else
			(*flags).statidoubles[0] |= (1LLU << VALID_D_FLG[index]);
		index++;
	}
}

void		ft_flinit(t_print *const restrict clipb, t_flag *flags)
{
	(*clipb).flags = flags;
	(*flags).statiflags[0] = 0;
	(*flags).statiflags[1] = 0;
	(*flags).statidoubles[0] = 0;
	(*flags).statidoubles[1] = 0;
	init_dflags(flags);
	init_flags(flags);
}
