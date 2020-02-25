/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 15:42:31 by aholster       #+#    #+#                */
/*   Updated: 2020/02/25 09:42:40 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

void	*ft_memcpy(void *const dst,\
			const void *const src,\
			const size_t n)
{
	size_t				offset;
	char *const			cdst = dst;
	const char *const	csrc = src;

	offset = 0;
	while (n - offset >= 8)
	{
		*((long long *)(cdst + offset)) = *((const long long *)(csrc + offset));
		offset += 8;
	}
	while (offset < n)
	{
		*(cdst + offset) = *(csrc + offset);
		offset++;
	}
	return (dst);
}
