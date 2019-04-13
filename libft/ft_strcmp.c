/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 12:25:24 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 21:26:54 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char const *s1, char const *s2)
{
	size_t	index;

	index = 0;
	while (s1[index] == s2[index] && s2[index] != '\0' && s1[index] != '\0')
	{
		index++;
	}
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}
