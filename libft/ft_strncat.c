/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 19:04:20 by aholster       #+#    #+#                */
/*   Updated: 2019/01/30 14:26:51 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, char const *s2, size_t n)
{
	size_t	index;
	size_t	judex;

	index = 0;
	judex = ft_strlen(s1);
	while (s2[index] != '\0' && index < n)
	{
		s1[index + judex] = s2[index];
		index++;
	}
	s1[index + judex] = '\0';
	return (s1);
}
