/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flinit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:44:14 by aholster       #+#    #+#                */
/*   Updated: 2019/10/01 15:31:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static void	init_flags(t_flag *const restrict flags)
{
	size_t	index;
	short	flip;

	index = 0;
	while (VALID_FLG[index] != '\0')
	{
		flip = VALID_FLG[index] / 32;
		flags->statiflags[flip] |= (1 << ((VALID_FLG[index]) - 32));
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
		flip = VALID_D_FLG[index] / 32;
		flags->statidoubles[flip] |= (1 << ((VALID_D_FLG[index]) - 32));
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
