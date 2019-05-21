/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/18 16:02:34 by aholster       #+#    #+#                */
/*   Updated: 2019/04/30 19:06:47 by aholster      ########   odam.nl         */
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
	ft_memcpy(ret, src, len);
	return ((void *)ret);
}
