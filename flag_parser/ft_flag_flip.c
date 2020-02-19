/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_flip.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 21:30:50 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 10:29:24 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag_parser.h"

void			ft_flag_flip(const char *const format,\
					size_t *const aindex,\
					t_writer *const clipb)
{
	const unsigned char		c = format[*aindex];
	const unsigned short	flip = c / FLG_UNS;
	t_flag *const			flags = clipb->flags;

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
