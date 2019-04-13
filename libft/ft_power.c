/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_power.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 20:20:36 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 18:49:05 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int num, unsigned int power)
{
	long long	calc;

	calc = 1;
	if (power == 0)
	{
		return (1);
	}
	while (power > 0)
	{
		calc = num * calc;
		if (calc > 2147483647 || calc < -2147483648)
			return (0);
		power--;
	}
	if (num < 0)
	{
		calc = (int)ft_absneg(calc);
	}
	return ((int)calc);
}
