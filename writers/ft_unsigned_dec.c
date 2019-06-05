/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsigned_dec.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 19:12:27 by aholster       #+#    #+#                */
/*   Updated: 2019/05/31 15:20:36 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned short	longlen(unsigned long long n)
{
	unsigned short	length;

	length = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

static unsigned short	unsigned_ll_toa(unsigned char *buffer,\
									unsigned long long holder)
{
	unsigned short	len;
	unsigned short	curlen;
	char			*base;

	base = "0123456789";
	len = longlen(holder) - 1;
	curlen = len;
	while (holder >= 10)
	{
		buffer[curlen] = base[(holder % 10)];
		holder /= 10;
		curlen--;
	}
	buffer[curlen] = base[holder];
	return (len + 1);
}

int		ft_unsigned_dec(va_list ap, t_print	*clipb)
{
	unsigned char		buffer[20];
	unsigned long long	num;
	unsigned short		numlen;

	num = va_arg(ap, unsigned long long);
	numlen = unsigned_ll_toa(buffer, num);
	va_end(ap);
	if (clipb->printer(buffer, numlen, clipb) == -1)
		return (-1);
	return (1);
}
