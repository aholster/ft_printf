/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 21:06:47 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 21:27:22 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	size_t index;

	index = 0;
	while (s[index] != '\0')
	{
		((*f)(&s[index]));
		index++;
	}
}
