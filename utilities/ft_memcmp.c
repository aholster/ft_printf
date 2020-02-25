/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 18:57:47 by aholster       #+#    #+#                */
/*   Updated: 2020/02/25 10:11:07 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

static int	smallcheck(char const *s1, char const *s2, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
	{
		if (s1[index] != s2[index])
		{
			return ((unsigned char)(s1[index]) - (unsigned char)(s2[index]));
		}
		index++;
	}
	return (0);
}

int			ft_memcmp(void const *s1, void const *s2, size_t n)
{
	size_t			offset;
	char const		*cs1;
	char const		*cs2;

	cs1 = s1;
	cs2 = s2;
	offset = 0;
	while (n - offset >= sizeof(long long))
	{
		if (((long long *)s1)[offset] != ((long long *)s2)[offset])
			break ;
		offset += sizeof(size_t);
	}
	return (smallcheck(cs1 + offset, cs2 + offset, n - offset));
}
