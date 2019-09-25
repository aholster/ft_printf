/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_functblinit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 19:14:05 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/25 13:41:52 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static unsigned short	slider(unsigned char c)
{
	return (c - 'A');
}

static void				functbl_clear(t_formatter *functbl)
{
	unsigned short	index;

	index = 0;
	while (index < FUNCSIZE)
	{
		functbl[index] = NULL;
		index++;
	}
}

void					ft_functblinit(t_formatter *functbl)
{
	functbl_clear(functbl);
	functbl[slider('a')] = &ft_lowhexpoint;
	functbl[slider('A')] = &ft_caphexpoint;
	functbl[slider('c')] = &ft_char;
	functbl[slider('d')] = &ft_decimal;
	functbl[slider('e')] = &ft_lowsci;
	functbl[slider('E')] = &ft_capsci;
	functbl[slider('f')] = &ft_lowfltpoint;
	// functbl[slider('F')] = &ft_upprfltpoint;
	functbl[slider('g')] = &ft_lowshrthd;
	functbl[slider('G')] = &ft_capshrthd;
	functbl[slider('i')] = &ft_decimal;
	functbl[slider('n')] = &ft_n;
	functbl[slider('o')] = &ft_octal;
	functbl[slider('p')] = &ft_ptraddr;
	functbl[slider('s')] = &ft_str;
	functbl[slider('u')] = &ft_unsigned_dec;
	functbl[slider('x')] = &ft_lowhex;
	functbl[slider('X')] = &ft_caphex;
}
