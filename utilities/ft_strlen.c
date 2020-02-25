/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 13:39:30 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 10:44:01 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

static const char	*ft_unrolledlen(const uint64_t himagic,\
						const uint64_t lomagic,\
						unsigned long long *longword_ptr,\
						const char *segment)
{
	while (1)
	{
		if ((((*longword_ptr) - lomagic) & ~(*longword_ptr) & himagic) != 0)
		{
			segment = (const char *)(longword_ptr);
			if (segment[0] == '\0')
				return (segment);
			if (segment[1] == '\0')
				return (segment + 1);
			if (segment[2] == '\0')
				return (segment + 2);
			if (segment[3] == '\0')
				return (segment + 3);
			if (segment[4] == '\0')
				return (segment + 4);
			if (segment[5] == '\0')
				return (segment + 5);
			if (segment[6] == '\0')
				return (segment + 6);
			if (segment[7] == '\0')
				return (segment + 7);
		}
		longword_ptr++;
	}
}

size_t				ft_strlen(const char *s)
{
	const uint64_t				himagic = 0x8080808080808080L;
	const uint64_t				lomagic = 0x0101010101010101L;
	const char					*segment;
	unsigned long long			*longword_ptr;

	segment = s;
	while (((unsigned int)segment & 7) != 0)
	{
		if (*segment == '\0')
			return (segment - s);
		segment++;
	}
	longword_ptr = (unsigned long long *)segment;
	segment = ft_unrolledlen(himagic, lomagic, longword_ptr, segment);
	return (segment - s);
}
