/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_verficators.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 18:35:52 by aholster       #+#    #+#                */
/*   Updated: 2019/06/05 18:41:50 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		flagverif(const unsigned char c, const t_flag *flags)
{
	unsigned short	flip;

	flip = c / 64;
	if (((1LLU << (c - (flip * 64))) & flags->actiflags[flip]) > 0)
		return (1);
	return (-1);
}

int		doubleverif(const unsigned char c, const t_flag *flags)
{
	unsigned short	flip;

	flip = c / 64;
	if (((1LLU << (c - (flip * 64))) & flags->actidoubles[flip]) > 0)
		return (1);
	return (-1);
}
