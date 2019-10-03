/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_turn_on_flag.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 21:55:39 by aholster       #+#    #+#                */
/*   Updated: 2019/10/03 21:59:24 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag_parser.h"

void	ft_turn_on_flag(const char c, t_flag *const restrict flags)
{
	const unsigned short	flip = c / FLG_UNS;

	flags->actiflags[flip] |= (1LLU << (c - (flip * FLG_UNS)));
}
