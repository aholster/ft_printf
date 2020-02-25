/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 16:54:50 by aholster       #+#    #+#                */
/*   Updated: 2020/02/25 10:01:19 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

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
				if (len > sizeof(unsigned long long))
				{
					len -= sizeof(unsigned long long);
					*((unsigned long long *)((char *)dst + len)) =\
					*((const unsigned long long *)((char const *)src + len));
				}
				else
				{
					len--;
					((char *)dst)[len] = ((const char *)src)[len];
				}
			}
			return (dst);
		}
		dst = ft_memcpy(dst, src, len);
	}
	return (dst);
}
