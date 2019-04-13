/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 10:35:30 by aholster       #+#    #+#                */
/*   Updated: 2019/04/04 12:21:13 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s1)
{
	char	*output;

	output = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (output == NULL)
		return (NULL);
	output = ft_strcpy(output, s1);
	return (output);
}
