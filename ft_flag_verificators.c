/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_verificators.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 18:35:52 by aholster       #+#    #+#                */
/*   Updated: 2019/10/01 15:21:40 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

int		flagverif(const unsigned char c, const t_flag *const restrict flags)
{
	const unsigned short	flip = c / 32;

	if (((1 << (c - (flip * 32))) & flags->actiflags[flip]) > 0)
		return (1);
	return (-1);
}

int		doubleverif(const unsigned char c, const t_flag *const restrict flags)
{
	const unsigned short	flip = c / 32;

	if (((1 << (c - (flip * 32))) & flags->actidoubles[flip]) > 0)
		return (1);
	return (-1);
}
