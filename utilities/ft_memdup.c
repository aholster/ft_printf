/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/18 16:02:34 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 09:41:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

void	*ft_memdup(const void *const src, const size_t len)
{
	size_t						index;
	char						*ret;

	index = 0;
	ret = (char *)malloc(sizeof(char) * len);
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, src, len);
	return ((void *)ret);
}
