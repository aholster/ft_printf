/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowhex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 16:34:02 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 10:25:01 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static void				ft_lowhex_noprec(const char *const buffer,\
							const unsigned long long nb,\
							const unsigned short nb_len,\
							t_writer *const clipb)
{
	t_flag *const	flags = clipb->flags;
	const int		minus = flg_verif('-', flags);

	if (minus == -1 && flg_verif('0', flags) == -1)
	{
		ft_space_padder(nb_len, clipb);
	}
	if (flg_verif('#', flags) == 1 && nb != 0)
	{
		ft_write_wrap("0x", 2, clipb);
	}
	if (flg_verif('0', flags) == 1 && minus == -1)
	{
		ft_zero_padder(nb_len, clipb);
	}
	ft_write_wrap(buffer, ((size_t)nb_len), clipb);
	if (minus == 1 && flags->padding > nb_len)
	{
		ft_space_padder(nb_len, clipb);
	}
}

static void				ft_lowhex_prec(const char *const buffer,\
							const unsigned long long nb,\
							const unsigned short nb_len,\
							t_writer *const clipb)
{
	t_flag *const	flags = clipb->flags;
	const int		minus = flg_verif('-', flags);

	if (minus == -1 && flags->padding > nb_len)
	{
		ft_space_padder(nb_len, clipb);
	}
	if (flg_verif('#', flags) == 1 && nb != 0)
	{
		ft_write_wrap("0x", 2, clipb);
	}
	if (flags->precision > nb_len)
	{
		ft_zero_padder(nb_len, clipb);
	}
	ft_write_wrap(buffer, (size_t)nb_len, clipb);
	if (minus == 1 && flags->padding > nb_len)
	{
		ft_space_padder(nb_len, clipb);
	}
}

static unsigned short	ull_to_hex(char *const buffer,\
							unsigned long long nb)
{
	unsigned short		index;
	unsigned short		len;
	unsigned long long	tempnum;
	const char			base[] = "0123456789abcdef";

	if (nb == 0)
	{
		buffer[0] = '0';
		return (1);
	}
	tempnum = nb;
	len = 0;
	while (tempnum > 0)
	{
		tempnum >>= 4;
		len++;
	}
	index = len;
	while (index > 0)
	{
		index--;
		buffer[index] = base[nb & 0XFLLU];
		nb >>= 4;
	}
	return (len);
}

int						ft_lowhex(va_list args, t_writer *const clipb)
{
	char				buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;
	t_flag *const		flags = clipb->flags;
	int const			is_prec = flg_verif('.', flags);

	ft_unsignconv(args, &nb, flags);
	nb_len = ull_to_hex(buffer, nb);
	if (!(nb == 0 && is_prec == 1 && flags->padding == 0))
	{
		if (flg_verif('#', clipb->flags) == 1 && nb != 0 &&\
			flags->padding >= 2)
		{
			flags->padding -= 2;
		}
		if (nb == 0 && is_prec == 1 && flags->precision == 0)
			ft_strcpy(buffer, " ");
		if (is_prec == 1)
			ft_lowhex_prec(buffer, nb, nb_len, clipb);
		else
			ft_lowhex_noprec(buffer, nb, nb_len, clipb);
	}
	return (0);
}
