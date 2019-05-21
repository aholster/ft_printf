/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 18:31:48 by aholster       #+#    #+#                */
/*   Updated: 2019/05/01 17:36:36 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size1;
	size_t	size2;
	char	*str;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (size1 + size2 + 1));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, size1);
	ft_memcpy(&str[size1], s2, size2);
	str[size1 + size2] = '\0';
	return (str);
}
