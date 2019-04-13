/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strarrdel.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 21:03:28 by aholster       #+#    #+#                */
/*   Updated: 2019/01/31 21:25:04 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strarrdel(char ***ap)
{
	size_t	index;

	index = 0;
	while ((*ap)[index] != NULL)
	{
		ft_strdel(&((*ap)[index]));
		index++;
	}
	free(*ap);
	*ap = NULL;
}
