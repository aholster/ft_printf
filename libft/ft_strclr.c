/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strclr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 10:55:10 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 21:27:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char *s)
{
	size_t	index;

	index = 0;
	while (s[index] != '\0')
	{
		s[index] = '\0';
		index++;
	}
}
