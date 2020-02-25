/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 13:33:03 by aholster       #+#    #+#                */
/*   Updated: 2020/02/25 10:06:30 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	offset;
	char	*cs;

	cs = s;
	while (n > 0 && cs + 0 % sizeof(long long))
	{
		*cs = '\0';
		cs += 1;
		n--;
	}
	offset = 0;
	while (n - offset >= sizeof(long long))
	{
		*(long long *)(cs + offset) = 0ll;
		offset += sizeof(long long);
	}
	while (offset < n)
	{
		(cs)[offset] = '\0';
		offset++;
	}
}
