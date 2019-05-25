/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_padder.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 16:10:49 by aholster       #+#    #+#                */
/*   Updated: 2019/05/25 16:33:17 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pad_spaces(size_t amount, t_print *clipb)
{
	static const char	*spaces = "                                                                ";
	size_t				index;
	size_t				calc;

	index = 0;
	while (index < amount)
	{
		if (amount - index < sizeof(spaces))
			calc = amount - index;
		else
			calc = sizeof(spaces);
		clipb->printer((const unsigned char *)spaces, calc, clipb);
		index += calc;
	}
	return (amount);
}

int	pad_zero(size_t amount, t_print *clipb)
{
	static const char	*zeroes = "0000000000000000000000000000000000000000000000000000000000000000";
	size_t				index;
	size_t				calc;

	index = 0;
	while (index < amount)
	{
		if (amount - index < sizeof(zeroes))
			calc = amount - index;
		else
			calc = sizeof(zeroes);
		clipb->printer((const unsigned char *)zeroes, calc, clipb);
		index += calc;
	}
	return (amount);
}
