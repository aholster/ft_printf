/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 18:49:46 by aholster       #+#    #+#                */
/*   Updated: 2019/05/01 18:39:50 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, char const *s2)
{
	size_t	len;
	size_t	start;

	len = ft_strlen(s2);
	start = ft_strlen(s1);
	ft_memcpy((void*)(s1 + start), (const void*)s2, len);
	s1[len + start] = '\0';
	return (s1);
}
