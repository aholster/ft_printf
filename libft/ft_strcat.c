/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 18:49:46 by aholster       #+#    #+#                */
/*   Updated: 2019/01/29 19:30:54 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, char const *s2)
{
	size_t	index;
	size_t	judex;

	index = 0;
	judex = ft_strlen(s1);
	while (s2[index] != '\0')
	{
		s1[index + judex] = s2[index];
		index++;
	}
	s1[index + judex] = '\0';
	return (s1);
}
