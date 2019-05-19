/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_functblinit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 19:14:05 by jesmith        #+#    #+#                */
/*   Updated: 2019/05/19 16:10:28 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned short	slider(unsigned char c)
{
	return (c - 'A');
	// return ((c > 'Z') ? c - ('A' + 6) : c - 'A');
}

void					ft_functblinit(t_writer *functbl)
{
	// functbl[slider('a')] = ft_lowhexpoint;
	// functbl[slider('A')] = ft_upprhexpoint;
	// functbl[slider('c')] = ft_char;
	// functbl[slider('d')] = ft_decimal;
	// functbl[slider('e')] = ft_lowsci;
	// functbl[slider('E')] = ft_uprsci;
	// functbl[slider('f')] = ft_lowfltpoint;
	// functbl[slider('F')] = ft_upprfltpoint;
	// functbl[slider('g')] = ft_lowshrthd;
	// functbl[slider('G')] = ft_upprshrthd;
	// functbl[slider('i')] = ft_integer;
	// functbl[slider('n')] = ft_nothing;
	// functbl[slider('o')] = ft_octal;
	// functbl[slider('p')] = ft_ptraddr;
	functbl[slider('s')] = ft_str;
	// functbl[slider('u')] = ft_unsignedec;
	// functbl[slider('x')] = ft_lowunsignedhex;
	// functbl[slider('X')] = ft_upprunsignedhex;
}