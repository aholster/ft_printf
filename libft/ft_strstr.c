/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 14:27:21 by aholster       #+#    #+#                */
/*   Updated: 2019/01/30 14:30:55 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char const *haystack, char const *needle)
{
	size_t	index;
	size_t	judex;

	index = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[index] != '\0')
	{
		judex = 0;
		while (needle[judex] == haystack[index + judex] &&\
		haystack[index + judex] != '\0')
		{
			judex++;
		}
		if (needle[judex] == '\0')
			return ((char *)&haystack[index]);
		index++;
	}
	return (NULL);
}
