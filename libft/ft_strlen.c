/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 13:39:30 by aholster       #+#    #+#                */
/*   Updated: 2019/05/03 20:11:42 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_unrolledlen(unsigned long long *magic, \
				unsigned long long *longword_ptr, const char *segment, \
				const char *s)
{
	while (1)
	{
		if ((((*longword_ptr) - magic[1]) & ~(*longword_ptr) & magic[0]) != 0)
		{
			segment = (const char *)(longword_ptr);
			if (segment[0] == '\0')
				return (segment - s);
			if (segment[1] == '\0')
				return (segment - s + 1);
			if (segment[2] == '\0')
				return (segment - s + 2);
			if (segment[3] == '\0')
				return (segment - s + 3);
			if (segment[4] == '\0')
				return (segment - s + 4);
			if (segment[5] == '\0')
				return (segment - s + 5);
			if (segment[6] == '\0')
				return (segment - s + 6);
			if (segment[7] == '\0')
				return (segment - s + 7);
		}
		longword_ptr++;
	}
}

size_t			ft_strlen(char const *s)
{
	unsigned long long			magicmasks[2];
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
	magicmasks[0] = 0x8080808080808080L;
	magicmasks[1] = 0x0101010101010101L;
	return (ft_unrolledlen(magicmasks, longword_ptr, segment, s));
}

/*
**	for further optimization, study norm-uncompliant version below
** size_t			ft_strlen(char const *s)
** {
** 	unsigned long long			*holder;
** 	unsigned long long			himagic;
** 	unsigned long long			lomagic;
** 	const char					*segment;
** 	unsigned long long			longword;
**
** 	segment = s;
** 	while ((unsigned int)segment % 8 != 0)
** 	{
** 		if (*segment == '\0')
** 			return (segment - s);
** 		segment++;
** 	}
**	holder = (unsigned long long *)segment;
** 	himagic = 0x8080808080808080L;
** 	lomagic = 0x0101010101010101L;
** 	while (1)
** 	{
** 		longword = *holder;
** 		if (((longword - lomagic) & ~longword & himagic) != 0)
** 		{
** 			segment = (const char *)(holder);
** 			if (segment[0] == '\0')
** 				return (segment - s);
** 			if (segment[1] == '\0')
** 				return (segment - s + 1);
** 			if (segment[2] == '\0')
** 				return (segment - s + 2);
** 			if (segment[3] == '\0')
** 				return (segment - s + 3);
** 			if (segment[4] == '\0')
** 				return (segment - s + 4);
** 			if (segment[5] == '\0')
** 				return (segment - s + 5);
** 			if (segment[6] == '\0')
** 				return (segment - s + 6);
** 			if (segment[7] == '\0')
** 				return (segment - s + 7);
** 		}
** 		holder++;
** 	}
** }
*/
