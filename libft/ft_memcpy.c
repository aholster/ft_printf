/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 15:42:31 by aholster       #+#    #+#                */
/*   Updated: 2019/05/18 16:00:23 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	index;

	index = 0;
	while (n - index >= 8)
	{
		*((long long *)(dst + index)) = *((const long long *)(src + index));
		index += 8;
	}
	while (index < n)
	{
		((char *)dst)[index] = ((const char *)src)[index];
		index++;
	}
	return (dst);
}
