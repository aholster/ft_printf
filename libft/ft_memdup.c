/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/18 16:02:34 by aholster       #+#    #+#                */
/*   Updated: 2019/02/18 17:34:27 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void *src, size_t len)
{
	size_t	index;
	char	*ret;
	char	*input;

	index = 0;
	input = src;
	ret = (char *)malloc(sizeof(char) * len);
	if (ret == NULL)
		return (NULL);
	while (index < len)
	{
		ret[index] = input[index];
		index++;
	}
	return ((void *)ret);
}
