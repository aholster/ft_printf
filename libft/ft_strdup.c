/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 10:35:30 by aholster       #+#    #+#                */
/*   Updated: 2019/05/01 18:29:01 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s1)
{
	char	*output;
	size_t	len;

	len = ft_strlen(s1);
	output = (char *)malloc(sizeof(char) * (len + 1));
	if (output == NULL)
		return (NULL);
	ft_memcpy((void *)output, (const void *)s1, len);
	output[len] = '\0';
	return (output);
}
