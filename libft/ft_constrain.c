/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_constrain.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 17:30:59 by aholster       #+#    #+#                */
/*   Updated: 2019/02/02 17:14:24 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_constrain(int in, int min, int max)
{
	if (min > max)
	{
		ft_swap(&min, &max);
	}
	if (in >= min && in <= max)
		return (in);
	else if (in < min)
		return (min);
	return (max);
}
