/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/16 15:25:40 by aholster       #+#    #+#                */
/*   Updated: 2019/05/01 17:40:33 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memjoin(const void *mem1, size_t size1,\
					const void *mem2, size_t size2)
{
	size_t	index;
	char	*ret;

	index = 0;
	ret = (char *)malloc(sizeof(char) * size1 + size2);
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, mem1, size1);
	ft_memcpy(&ret[size1], mem2, size2);
	return (ret);
}
