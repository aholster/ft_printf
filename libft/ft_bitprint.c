/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bitprint.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/27 15:51:49 by aholster       #+#    #+#                */
/*   Updated: 2019/03/27 18:39:13 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bitprint(const void *addr, size_t size)
{
	size_t			index;
	unsigned char	tmp;
	char			*boolea;

	index = 0;
	boolea = "01";
	while (index < size)
	{
		tmp = ((unsigned char *)addr)[index];
		write(1, &boolea[(tmp >> 7) & 1], 1);
		write(1, &boolea[(tmp >> 6) & 1], 1);
		write(1, &boolea[(tmp >> 5) & 1], 1);
		write(1, &boolea[(tmp >> 4) & 1], 1);
		write(1, &boolea[(tmp >> 3) & 1], 1);
		write(1, &boolea[(tmp >> 2) & 1], 1);
		write(1, &boolea[(tmp >> 1) & 1], 1);
		write(1, &boolea[(tmp >> 0) & 1], 1);
		if (index % 8 == 7)
			write(1, "\n", 1);
		else
			write(1, " ", 1);
		index++;
	}
}
