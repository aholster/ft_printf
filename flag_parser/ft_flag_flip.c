/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_flip.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 21:30:50 by aholster       #+#    #+#                */
/*   Updated: 2019/10/03 22:05:20 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag_parser.h"

void			ft_flag_flip(const char *const restrict format,\
					size_t *const restrict aindex,\
					t_writer *const restrict clipb)
{
	const unsigned char		c = format[*aindex];
	const unsigned short	flip = c / FLG_UNS;
	t_flag *const restrict	flags = clipb->flags;

	if (((1LLU << (c - (flip * FLG_UNS))) & flags->actiflags[flip]) > 0)
	{
		flags->actidoubles[flip] |= (1LLU << (c - (flip * FLG_UNS)));
		flags->actiflags[flip] ^= (1LLU << (c - (flip * FLG_UNS)));
	}
	else
	{
		flags->actiflags[flip] |= (1LLU << (c - (flip * FLG_UNS)));
		flags->actidoubles[flip] ^= (1LLU << (c - (flip * FLG_UNS)));
	}
	*aindex += 1;
}
