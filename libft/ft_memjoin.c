/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/16 15:25:40 by aholster       #+#    #+#                */
/*   Updated: 2019/02/18 17:34:47 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memjoin(void *mem1, size_t size1, void *mem2, size_t size2)
{
	size_t	index;
	size_t	judex;
	char	*ret;
	char	*src;

	index = 0;
	src = (char *)mem1;
	ret = (char *)malloc(sizeof(char) * size1 + size2);
	if (ret == NULL)
		return (NULL);
	while (index < size1)
	{
		ret[index] = src[index];
		index++;
	}
	src = (char *)mem2;
	judex = 0;
	while (judex < size2)
	{
		ret[index] = src[judex];
		index++;
		judex++;
	}
	return (ret);
}
