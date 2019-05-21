/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 19:04:20 by aholster       #+#    #+#                */
/*   Updated: 2019/05/01 18:39:48 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, char const *s2, size_t n)
{
	size_t	len;
	size_t	start;

	len = ft_strlen(s2);
	start = ft_strlen(s1);
	if (len >= n)
		len = n;
	ft_memcpy((void*)(s1 + start), (const void*)s2, len);
	s1[len + start] = '\0';
	return (s1);
}
