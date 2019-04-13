/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstrarr_fd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 21:00:21 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 16:03:05 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrarr_fd(char **strarr, int fd)
{
	size_t	index;

	index = 0;
	while (strarr[index] != NULL)
	{
		ft_putendl_fd(strarr[index], fd);
		index++;
	}
}
