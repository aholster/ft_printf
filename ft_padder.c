/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_padder.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 16:10:49 by aholster       #+#    #+#                */
/*   Updated: 2019/06/05 19:27:53 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pad_spaces(size_t amount, t_print *clipb)
{
	size_t		index;
	size_t		calc;
	const char	*spaces = "                                                                ";

	index = 0;
	while (index < amount)
	{
		if (amount - index < sizeof(spaces))
			calc = amount - index;
		else
			calc = sizeof(spaces);
		if (clipb->printer((const unsigned char *)spaces, calc, clipb) == -1)
			return (-1);
		index += calc;
	}
	return (amount);
}

int	pad_zero(size_t amount, t_print *clipb)
{
	size_t		index;
	size_t		calc;
	const char	*zeroes = "0000000000000000000000000000000000000000000000000000000000000000";

	index = 0;
	while (index < amount)
	{
		if (amount - index < sizeof(zeroes))
			calc = amount - index;
		else
			calc = sizeof(zeroes);
		if (clipb->printer((const unsigned char *)zeroes, calc, clipb) == -1)
			return (-1);
		index += calc;
	}
	return (amount);
}
