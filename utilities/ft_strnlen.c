/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnlen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 21:42:09 by aholster       #+#    #+#                */
/*   Updated: 2020/02/27 14:01:45 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

static int		unrolled_len(
					const unsigned long long *longword_ptr,
					const char **const asegment)
{
	const char *const	read_segment = (const char *)(longword_ptr);

	if (read_segment[0] == '\0')
		*asegment = read_segment;
	else if (read_segment[1] == '\0')
		*asegment = read_segment + 1;
	else if (read_segment[2] == '\0')
		*asegment = read_segment + 2;
	else if (read_segment[3] == '\0')
		*asegment = read_segment + 3;
	else if (read_segment[4] == '\0')
		*asegment = read_segment + 4;
	else if (read_segment[5] == '\0')
		*asegment = read_segment + 5;
	else if (read_segment[6] == '\0')
		*asegment = read_segment + 6;
	else if (read_segment[7] == '\0')
		*asegment = read_segment + 7;
	else
		return (0);
	return (1);
}

size_t			ft_strnlen(const char *s, size_t maxlen)
{
	const unsigned long long	*holder;
	const uint64_t				himagic = 0x8080808080808080L;
	const uint64_t				lomagic = 0x0101010101010101L;
	const char					*segment = s;
	unsigned long long			longword;

	while (((unsigned int)segment & 7) != 0)
	{
		if (*segment == '\0')
			return (segment - s);
		segment++;
	}
	holder = (unsigned long long *)segment;
	while (1)
	{
		longword = *holder;
		if (((longword - lomagic) & ~longword & himagic) != 0)
		{
			if (unrolled_len(holder, &segment) == 1)
				return (segment - s);
		}
		if ((const char *)holder + 8 > maxlen + s)
			return (maxlen);
		holder++;
	}
}
