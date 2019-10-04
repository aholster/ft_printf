/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 15:05:30 by aholster       #+#    #+#                */
/*   Updated: 2019/10/04 19:09:20 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

static void	ft_bigset(void *restrict b,\
				const unsigned char c,\
				const size_t len,\
				size_t *const restrict index)
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

void		*ft_memset(void *restrict b, const int c, const size_t len)
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
