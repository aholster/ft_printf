/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 18:57:47 by aholster       #+#    #+#                */
/*   Updated: 2019/04/30 19:43:47 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	smallcheck(void const *s1, void const *s2, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
	{
		if (((unsigned char const *)s1)[index] !=\
			((unsigned char const *)s2)[index])
		{
			return (((unsigned char const *)s1)[index] - \
				((unsigned char const *)s2)[index]);
		}
		index++;
	}
	return (0);
}

int			ft_memcmp(void const *s1, void const *s2, size_t n)
{
	size_t			index;

	index = 0;
	while (n - (index * 8) >= 8)
	{
		if (((long long *)s1)[index] != ((long long *)s2)[index])
			break ;
		index++;
	}
	return (smallcheck(s1 + (index * 8), s2 + (index * 8), n - (index * 8)));
}
