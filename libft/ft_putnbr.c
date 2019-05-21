/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 18:18:57 by aholster       #+#    #+#                */
/*   Updated: 2019/05/08 18:44:47 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	char	buf[11];
	size_t	curlen;
	size_t	len;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
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
		write(1, buf, len + 1);
	}
}

/*
** void	ft_putnbr(int n)
** {
** 	if (n == -2147483648)
** 	{
** 		write(1, "-2", 2);
** 		n = 147483648;
** 	}
** 	else if (n < 0)
** 	{
** 		write(1, "-", 1);
** 		n = (-n);
** 	}
** 	if (n > 9)
** 	{
** 		ft_putnbr(n / 10);
** 		ft_putchar((n % 10) + '0');
** 	}
** 	else
** 		ft_putchar(n + '0');
** }
*/
