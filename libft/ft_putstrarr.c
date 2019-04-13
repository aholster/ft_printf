/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstrarr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 20:51:13 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 16:10:39 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrarr(char **strarr)
{
	size_t	index;

	index = 0;
	while (strarr[index] != NULL)
	{
		ft_putendl(strarr[index]);
		index++;
	}
}
