/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 15:05:30 by aholster       #+#    #+#                */
/*   Updated: 2019/05/01 17:27:56 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_bigset(void *b, unsigned char c, size_t len, size_t *index)
{
	unsigned long long	longword;
	size_t				megadex;

	megadex = 0;
	longword = c;
	longword |= (longword << 8);
	longword |= (longword << 16);
	longword |= (longword << 32);
	while (len - megadex >= 8)
	{
		*((long long *)(b + megadex)) = longword;
		megadex += 8;
	}
	*index += megadex;
}

void		*ft_memset(void *b, int c, size_t len)
{
	size_t	index;

	index = 0;
	if (len > 16)
	{
		while ((int)b % 8 != 0)
		{
			*((unsigned char *)b) = (unsigned char)c;
			b++;
		}
		ft_bigset(b, (unsigned char)c, len, &index);
	}
	while (index < len)
	{
		((unsigned char *)b)[index] = (unsigned char)c;
		index++;
	}
	return (b);
}
