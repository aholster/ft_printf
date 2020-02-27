/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptraddr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 13:19:52 by aholster       #+#    #+#                */
/*   Updated: 2020/02/27 09:01:54 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static void				ft_ptraddr_noprec(const char *const buffer,\
							const unsigned short num_len,\
							t_writer *const clipb)
{
	t_flag *const	flags = clipb->flags;
	const int		minus = flg_verif('-', flags);

	if (minus == -1 && flg_verif('0', flags) == -1)
	{
		ft_space_padder(num_len, clipb);
	}
	ft_write_wrap("0x", 2, clipb);
	if (flg_verif('0', flags) == 1 && minus == -1)
	{
		ft_zero_padder(num_len, clipb);
	}
	ft_write_wrap(buffer, num_len, clipb);
	if (minus == 1 && flags->padding > num_len)
	{
		ft_space_padder(num_len, clipb);
	}
}

static void				ft_ptraddr_prec(const char *const buffer,\
							const unsigned short num_len,\
							t_writer *const clipb)
{
	t_flag *const	flags = clipb->flags;
	const int		minus = flg_verif('-', flags);

	if (minus == -1 && flags->padding > num_len)
	{
		ft_space_padder(num_len, clipb);
	}
	ft_write_wrap("0x", 2, clipb);
	if (flg_verif('.', flags) == 1 && flags->precision > num_len)
	{
		ft_zero_padder(num_len, clipb);
	}
	ft_write_wrap(buffer, num_len, clipb);
	if (minus == 1 && flags->padding > num_len)
	{
		ft_space_padder(num_len, clipb);
	}
}

static unsigned short	unsigned_ll_toa(char *const buffer,\
							unsigned long long holder)
{
	unsigned short	num_len;
	unsigned short	curlen;
	const char		base[] = "0123456789abcdef";

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

int						ft_ptraddr(va_list args, t_writer *const clipb)
{
	unsigned long long	holder;
	unsigned short		num_len;
	char				buffer[20];
	t_flag *const		flags = clipb->flags;

	holder = (unsigned long long)va_arg(args, void*);
	num_len = unsigned_ll_toa(buffer, holder);
	if (holder == 0 && flg_verif('.', flags) == 1 && flags->precision == 0)
	{
		num_len--;
	}
	if (flg_verif('.', flags) == 1)
	{
		if (flags->padding >= 2)
			flags->padding -= 2;
		ft_ptraddr_prec(buffer, num_len, clipb);
	}
	else
	{
		if (flags->padding >= 2)
			flags->padding -= 2;
		ft_ptraddr_noprec(buffer, num_len, clipb);
	}
	return (0);
}
