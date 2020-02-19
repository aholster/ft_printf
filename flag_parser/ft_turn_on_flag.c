/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_turn_on_flag.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 21:55:39 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 09:41:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag_parser.h"

void	ft_turn_on_flag(const char c, t_flag *const flags)
{
	const unsigned short	flip = c / FLG_UNS;

	flags->actiflags[flip] |= (1LLU << (c - (flip * FLG_UNS)));
}
