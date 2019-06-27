/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_functblinit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 19:14:05 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/25 10:51:54 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned short	slider(unsigned char c)
{
	return (c - 'A');
}

void					ft_functblinit(t_writer *functbl)
{
	// functbl[slider('a')] = ft_lowhexpoint;
	// functbl[slider('A')] = ft_upprhexpoint;
	functbl[slider('c')] = ft_char;
	functbl[slider('d')] = ft_decimal;
	functbl[slider('e')] = ft_lowsci;
	// functbl[slider('E')] = ft_uprsci;
	// functbl[slider('f')] = ft_lowfltpoint;
	// functbl[slider('F')] = ft_upprfltpoint;
	// functbl[slider('g')] = ft_lowshrthd;
	// functbl[slider('G')] = ft_upprshrthd;
	functbl[slider('i')] = ft_decimal;
	functbl[slider('n')] = ft_n;
	functbl[slider('o')] = ft_octal;
	functbl[slider('p')] = ft_ptraddr;
	functbl[slider('s')] = ft_str;
	functbl[slider('u')] = ft_unsigned_dec;
	functbl[slider('x')] = ft_lowhex;
	functbl[slider('X')] = ft_caphex;
}
