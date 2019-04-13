/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 16:33:42 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 21:26:21 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void const *src, int c, size_t n)
{
	unsigned char		*output;
	unsigned char const	*input;
	size_t				index;

	index = 0;
	output = dst;
	input = src;
	while (index < n && input[index] != (unsigned char)c)
	{
		output[index] = input[index];
		index++;
	}
	if (index == n)
		return (NULL);
	if (input[index] == (unsigned char)c)
	{
		output[index] = input[index];
		return ((void *)&output[index + 1]);
	}
	return (NULL);
}
