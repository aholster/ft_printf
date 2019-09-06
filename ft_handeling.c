/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handeling.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/06 10:44:11 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/06 10:46:43 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_shortprec(unsigned char *buffer, unsigned short nb_len, \
	t_print *clipb)
{
	size_t index;
	size_t holder;

	index = nb_len;
	holder = 0;
	while (index < clipb->flags->precision)
	{
		while (buffer[index] != '0' && index < clipb->flags->precision + 1)
			index++;
		if (buffer[index] == '0' && index < clipb->flags->precision + 1)
		{
			holder = index - 1;
			while (buffer[index] == '0' && index < clipb->flags->precision + 1)
				index++;
		}
	}
	if (index > holder && holder != 0)
		clipb->flags->precision = index - holder;
}

int				ft_prefix(int neg, t_print *clipb)
{
	if (neg != -1)
	{
		if (flagverif('+', clipb->flags) == 1)
			if (clipb->printer((const unsigned char*)"+", 1, clipb) == -1)
				return (-1);
		if (flagverif(' ', clipb->flags) == 1 && \
		flagverif('+', clipb->flags) == -1)
		{
			if (clipb->printer((const unsigned char*)" ", 1, clipb) == -1)
				return (-1);
		}
	}
	else if (clipb->printer((const unsigned char*)"-", 1, clipb) == -1)
		return (-1);
	return (1);
}
