/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 12:05:42 by aholster       #+#    #+#                */
/*   Updated: 2019/05/08 18:46:57 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	buf[11];
	size_t	curlen;
	size_t	len;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		curlen = ft_nbrlen(n, 10) - 1;
		if (n < 0)
		{
			buf[0] = '-';
			n = (-n);
		}
		len = curlen;
		while (n > 9)
		{
			buf[curlen] = (n % 10) + '0';
			n /= 10;
			curlen--;
		}
		buf[curlen] = (n + '0');
		write(fd, buf, len + 1);
	}
}
