/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flgdbl_verif.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 19:43:47 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 09:41:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_internals.h"

int		flgdbl_verif(const unsigned char c, const t_flag *const flags)
{
	const unsigned short	flip = c / FLG_UNS;

	if (((1LLU << (c - (flip * FLG_UNS))) & flags->actidoubles[flip]) > 0)
		return (1);
	return (-1);
}
