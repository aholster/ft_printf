/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strarrnew.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/24 17:49:47 by aholster       #+#    #+#                */
/*   Updated: 2019/03/24 17:56:30 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarrnew(size_t size)
{
	char	**str;

	str = (char **)malloc(sizeof(char *) * size + 1);
	if (str == NULL)
		return (NULL);
	str[size] = NULL;
	return (str);
}
