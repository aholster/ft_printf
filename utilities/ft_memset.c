/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 15:05:30 by aholster       #+#    #+#                */
/*   Updated: 2020/02/27 14:52:51 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

static void	ft_bigset(char *b,
				const unsigned char c,
				const size_t len,
				size_t *const index)
{
	unsigned long long	longword;
	size_t				megadex;

	megadex = 0;
	longword = c;
	longword |= (longword << 8);
	longword |= (longword << 16);
	longword |= (longword << 32);
	while (len - megadex >= sizeof(unsigned long long))
	{
		*((long long *)(b + megadex)) = longword;
		megadex += sizeof(unsigned long long);
	}
	*index += megadex;
}

void		*ft_memset(void *b, const int c, const size_t len)
{
	size_t	index;
	char	*cb;

	index = 0;
	cb = b;
	if (len > 16)
	{
		while (((int)cb % sizeof(unsigned long long)) != 0)
		{
			*((char *)cb) = (char)c;
			cb++;
		}
		ft_bigset(cb, (unsigned char)c, len, &index);
	}
	while (index < len)
	{
		((char *)cb)[index] = (char)c;
		index++;
	}
	return (b);
}
