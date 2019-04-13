/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memalloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 14:56:57 by aholster       #+#    #+#                */
/*   Updated: 2019/01/29 18:32:34 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *output;

	output = (void *)malloc(sizeof(void *) * size);
	if (output == NULL)
		return (NULL);
	ft_memset(output, '\0', size);
	return (output);
}
