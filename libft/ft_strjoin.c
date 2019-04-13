/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 18:31:48 by aholster       #+#    #+#                */
/*   Updated: 2019/04/06 15:02:19 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	size_t	judex;
	char	*str;

	judex = 0;
	index = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[judex] != '\0')
	{
		str[judex] = s1[judex];
		judex++;
	}
	while (s2[index] != '\0')
	{
		str[judex + index] = s2[index];
		index++;
	}
	str[judex + index] = '\0';
	return (str);
}
