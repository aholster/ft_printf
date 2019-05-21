/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stralloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/24 18:08:35 by aholster       #+#    #+#                */
/*   Updated: 2019/05/01 17:40:21 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stralloc(size_t size, char c)
{
	char	*str;
	size_t	index;

	index = 0;
	str = (char *)malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	ft_memset((void *)str, (int)c, size);
	return (str);
}
