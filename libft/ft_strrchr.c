/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 13:02:34 by aholster       #+#    #+#                */
/*   Updated: 2019/01/30 14:29:30 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	size_t			index;

	index = ft_strlen(s);
	while (index != 0)
	{
		if (s[index] == (unsigned char)c)
			return ((char *)&s[index]);
		index--;
	}
	if (s[index] == (unsigned char)c)
		return ((char *)&s[index]);
	return (NULL);
}
