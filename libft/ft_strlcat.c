/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/20 16:37:37 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 20:52:24 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t	output;
	size_t	sourcelen;
	size_t	index;

	index = 0;
	output = 0;
	sourcelen = ft_strlen(src);
	while (dst[output] != '\0' && output < size)
		output++;
	if (output + 1 >= size)
		return (output + sourcelen);
	else
	{
		while (index + output < size - 1)
		{
			dst[index + output] = src[index];
			index++;
		}
		dst[size - 1] = '\0';
	}
	return (output + sourcelen);
}
