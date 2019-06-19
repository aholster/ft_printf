/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptraddr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 13:19:52 by aholster       #+#    #+#                */
/*   Updated: 2019/06/19 15:10:11 by jesmith       ########   odam.nl         */
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
		n = n / 16;
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

	base = "0123456789abcdef";
	len = longlen(holder) - 1;
	curlen = len;
	while (holder >= 16)
	{
		buffer[curlen] = base[(holder % 16)];
		holder /= 16;
		curlen--;
	}
	buffer[curlen] = base[holder];
	return (len + 1);
}

static int				ft_ptraddr_prec(unsigned char *buffer,\
								unsigned short numlen, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1 && clipb->flags->padding > (clipb->flags->precision + 2))
	{
		if (pad_spaces(clipb->flags->padding - (clipb->flags->precision + 2), clipb) == -1)
			return (-1);
	}
	if (clipb->printer((const unsigned char *)"0x", 2, clipb) == -1)
	{
		return (-1);
	}
	if (flagverif('.', clipb->flags) == 1 && clipb->flags->precision > numlen)
	{
		if (pad_zero(clipb->flags->precision - numlen, clipb) == -1)
			return (-1);
	}
	if (clipb->printer(buffer, numlen, clipb) == -1)
	{
		return (-1);
	}
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > (clipb->flags->precision + 2))
	{
		if (pad_spaces(clipb->flags->padding - (clipb->flags->precision + 2), clipb) == -1)
			return (-1);
	}
	return (1);
}

int						ft_ptraddr(va_list args, t_print *clipb)
{
	unsigned long long	holder;
	unsigned short		numlen;
	unsigned char		buffer[16];

	holder = (unsigned long long)va_arg(args, void*);
	numlen = unsigned_ll_toa(buffer, holder);
	if (flagverif('.', clipb->flags) == 1)
		return (ft_ptraddr_prec(buffer, numlen, clipb));
	if (flagverif('-', clipb->flags) == -1 && clipb->flags->padding > (numlen + 2))
		if (pad_spaces(clipb->flags->padding - (numlen + 2), clipb) == -1)
			return (-1);
	if (clipb->printer((const unsigned char *)"0x", 2, clipb) == -1)
		return (-1);
	if (clipb->printer(buffer, numlen, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > (numlen + 2))
		if (pad_spaces(clipb->flags->padding - (numlen + 2), clipb) == -1)
			return (-1);
	return (1);
}
