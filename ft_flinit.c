/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flinit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:44:14 by aholster       #+#    #+#                */
/*   Updated: 2019/10/02 17:37:50 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/ft_internals.h"

static void	init_flags(t_flag *const restrict flags)
{
	size_t	index;
	short	flip;

	index = 0;
	while (VALID_FLG[index] != '\0')
	{
		flip = VALID_FLG[index] / FLG_UNS;
		flags->statiflags[flip] |= (1LLU << (VALID_FLG[index] - (FLG_UNS * flip)));
		index++;
	}
}

static void	init_dflags(t_flag *const restrict flags)
{
	size_t	index;
	short	flip;

	index = 0;
	while (VALID_D_FLG[index] != '\0')
	{
		flip = VALID_D_FLG[index] / FLG_UNS;
		flags->statidoubles[flip] |= (1LLU << ((VALID_D_FLG[index]) - (FLG_UNS * flip)));
		index++;
	}
}

void		ft_flinit(t_writer *const restrict clipb,\
				t_flag *const restrict flags)
{
	(*clipb).flags = flags;
	ft_bzero(flags, sizeof(t_flag));
	init_dflags(flags);
	init_flags(flags);
}
