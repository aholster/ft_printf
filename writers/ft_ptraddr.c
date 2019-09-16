/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptraddr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 13:19:52 by aholster       #+#    #+#                */
/*   Updated: 2019/09/13 17:34:59 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				ft_ptraddr_noprec(char *buffer, \
					unsigned short num_len, t_print *clipb)
{
	int minus;

	minus = flagverif('-', clipb->flags);
	if (minus == -1 && flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(num_len, clipb) == -1)
			return (-1);
	if (clipb->printer("0x", 2, clipb) == -1)
		return (-1);
	if (flagverif('0', clipb->flags) == 1 && minus == -1)
		if (ft_zero_padder(num_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, num_len, clipb) == -1)
		return (-1);
	if (minus == 1 && clipb->flags->padding > num_len)
		if (ft_space_padder(num_len, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_ptraddr_prec(char *buffer,\
								unsigned short num_len, t_print *clipb)
{
	int minus;

	minus = flagverif('-', clipb->flags);
	if (minus == -1 && clipb->flags->padding > num_len)
		if (ft_space_padder(num_len, clipb) == -1)
			return (-1);
	if (clipb->printer("0x", 2, clipb) == -1)
		return (-1);
	if (flagverif('.', clipb->flags) == 1 && clipb->flags->precision > num_len)
		if (ft_zero_padder(num_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, num_len, clipb) == -1)
		return (-1);
	if (minus == 1 && clipb->flags->padding > num_len)
		if (ft_space_padder(num_len, clipb) == -1)
			return (-1);
	return (1);
}

static unsigned short	unsigned_ll_toa(char *buffer,\
									unsigned long long holder)
{
	unsigned short	num_len;
	unsigned short	curlen;
	char			*base;

	base = "0123456789abcdef";
	num_len = ft_ull_len(holder, 16);
	curlen = num_len - 1;
	while (holder >= 16)
	{
		buffer[curlen] = base[(holder % 16)];
		holder /= 16;
		curlen--;
	}
	buffer[curlen] = base[holder];
	return (num_len);
}

int						ft_ptraddr(va_list args, t_print *clipb)
{
	unsigned long long	holder;
	unsigned short		num_len;
	char				buffer[20];

	holder = (unsigned long long)va_arg(args, void*);
	num_len = unsigned_ll_toa(buffer, holder);
	if (flagverif('.', clipb->flags) == 1)
	{
		if (clipb->flags->padding >= 2)
			clipb->flags->padding -= 2;
		return (ft_ptraddr_prec(buffer, num_len, clipb));
	}
	if (flagverif('.', clipb->flags) == -1)
	{
		if (clipb->flags->padding >= 2)
			clipb->flags->padding -= 2;
		return (ft_ptraddr_noprec(buffer, num_len, clipb));
	}
	return (1);
}
