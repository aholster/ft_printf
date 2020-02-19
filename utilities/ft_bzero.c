/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 13:33:03 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 09:41:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	index;

	index = 0;
	while (n > 0 && s + 0 % 8)
	{
		((char*)s)[index] = '\0';
		s++;
		n--;
	}
	while (n - (index * 8) >= 8)
	{
		((long long *)s)[index] = 0ll;
		index++;
	}
	index *= 8;
	while (index < n)
	{
		((char *)s)[index] = '\0';
		index++;
	}
}
