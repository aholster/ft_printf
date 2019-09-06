/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 16:54:50 by aholster       #+#    #+#                */
/*   Updated: 2019/09/03 20:45:50 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void const *src, size_t len)
{
	if (len != 0)
	{
		if (dst == NULL && src == NULL)
			return (dst);
		if (src < dst)
		{
			while (len != 0)
			{
				if (len > 8)
				{
					len -= 8;
					*((unsigned long long *)(dst + len)) =\
					*((const unsigned long long *)(src + len));
				}
				else
				{
					len--;
					((char *)dst)[len] = ((char const *)src)[len];
				}
			}
			return (dst);
		}
		dst = ft_memcpy(dst, src, len);
	}
	return (dst);
}
