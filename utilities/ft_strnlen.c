/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlnlen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/08 21:42:09 by aholster       #+#    #+#                */
/*   Updated: 2019/10/08 21:42:27 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

static int		unrolled_len(char const **const asegment)
{
	const char *const	segment = *asegment;

	if (segment[0] == '\0')
		*asegment = *asegment;
	else if (segment[1] == '\0')
		*asegment = *asegment + 1;
	else if (segment[2] == '\0')
		*asegment = *asegment + 2;
	else if (segment[3] == '\0')
		*asegment = *asegment + 3;
	else if (segment[4] == '\0')
		*asegment = *asegment + 4;
	else if (segment[5] == '\0')
		*asegment = *asegment + 5;
	else if (segment[6] == '\0')
		*asegment = *asegment + 6;
	else if (segment[7] == '\0')
		*asegment = *asegment + 7;
	else
		return (0);
	return (1);
}

size_t			ft_strnlen(char const *s, size_t maxlen)
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
			if (unrolled_len((const char **const)&holder) == 1)
				return (segment - s);
		}
		if ((const char *)holder + 8 > maxlen + s)
			return (maxlen);
		holder++;
	}
}
