/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptraddr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 13:19:52 by aholster       #+#    #+#                */
/*   Updated: 2019/10/04 17:57:03 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int				ft_ptraddr_noprec(const char *const restrict buffer,\
							const unsigned short num_len,\
							t_writer *const restrict clipb)
{
	t_flag *const restrict	flags = clipb->flags;
	const int				minus = flg_verif('-', flags);

	if (minus == -1 && flg_verif('0', flags) == -1)
		if (ft_space_padder(num_len, clipb) == -1)
			return (-1);
	if (clipb->self("0x", 2, clipb) == -1)
		return (-1);
	if (flg_verif('0', flags) == 1 && minus == -1)
		if (ft_zero_padder(num_len, clipb) == -1)
			return (-1);
	if (clipb->self(buffer, num_len, clipb) == -1)
		return (-1);
	if (minus == 1 && flags->padding > num_len)
		if (ft_space_padder(num_len, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_ptraddr_prec(const char *const restrict buffer,\
							const unsigned short num_len,\
							t_writer *const restrict clipb)
{
	t_flag *const restrict	flags = clipb->flags;
	const int				minus = flg_verif('-', flags);

	if (minus == -1 && flags->padding > num_len)
		if (ft_space_padder(num_len, clipb) == -1)
			return (-1);
	if (clipb->self("0x", 2, clipb) == -1)
		return (-1);
	if (flg_verif('.', flags) == 1 && flags->precision > num_len)
		if (ft_zero_padder(num_len, clipb) == -1)
			return (-1);
	if (clipb->self(buffer, num_len, clipb) == -1)
		return (-1);
	if (minus == 1 && flags->padding > num_len)
		if (ft_space_padder(num_len, clipb) == -1)
			return (-1);
	return (1);
}

static unsigned short	unsigned_ll_toa(char *const restrict buffer,\
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

int						ft_ptraddr(va_list args, t_writer *const restrict clipb)
{
	unsigned long long		holder;
	unsigned short			num_len;
	char					buffer[20];
	t_flag *const restrict	flags = clipb->flags;

	holder = (unsigned long long)va_arg(args, void*);
	num_len = unsigned_ll_toa(buffer, holder);
	if (flg_verif('.', flags) == 1)
	{
		if (flags->padding >= 2)
			flags->padding -= 2;
		return (ft_ptraddr_prec(buffer, num_len, clipb));
	}
	if (flg_verif('.', clipb->flags) == -1)
	{
		if (flags->padding >= 2)
			flags->padding -= 2;
		return (ft_ptraddr_noprec(buffer, num_len, clipb));
	}
	return (1);
}
