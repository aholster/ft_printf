/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 16:54:50 by aholster       #+#    #+#                */
/*   Updated: 2019/02/16 17:58:24 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void const *src, size_t len)
{
	unsigned char		*output;
	unsigned char const	*input;
	size_t				index;

	index = 0;
	output = (unsigned char *)dst;
	input = (unsigned char const *)src;
	while (index < len)
	{
		if (&dst[0] == &input[index])
		{
			while (len != 0)
			{
				len--;
				output[len] = input[len];
			}
			return (dst);
		}
		index++;
	}
	dst = ft_memcpy(dst, src, len);
	return (dst);
}
