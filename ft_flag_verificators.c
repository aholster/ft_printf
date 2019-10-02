/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_verificators.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 18:35:52 by aholster       #+#    #+#                */
/*   Updated: 2019/10/02 17:42:51 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/ft_internals.h"

int		flagverif(const unsigned char c, const t_flag *const restrict flags)
{
	const unsigned short	flip = c / FLG_UNS;

	if (((1LLU << (c - (flip * FLG_UNS))) & flags->actiflags[flip]) > 0)
		return (1);
	return (-1);
}

int		doubleverif(const unsigned char c, const t_flag *const restrict flags)
{
	const unsigned short	flip = c / FLG_UNS;

	if (((1LLU << (c - (flip * FLG_UNS))) & flags->actidoubles[flip]) > 0)
		return (1);
	return (-1);
}
