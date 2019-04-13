/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 15:05:30 by aholster       #+#    #+#                */
/*   Updated: 2019/02/16 17:59:10 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	character;
	size_t			index;
	char			*output;

	character = c;
	index = 0;
	output = (char *)b;
	while (index < len)
	{
		output[index] = character;
		index++;
	}
	return (b);
}
