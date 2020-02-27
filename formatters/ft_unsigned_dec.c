/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsigned_dec.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 19:12:27 by aholster       #+#    #+#                */
/*   Updated: 2020/02/27 10:28:35 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static void				ft_unsigned_dec_noprec(\
							const char *const buffer,\
							const unsigned short nb_len,\
							t_writer *const clipb)
{
	t_flag *const	flags = clipb->flags;
	const int		minus = flg_verif('-', flags);

	if (minus == -1 && flg_verif('0', flags) == -1)
	{
		ft_space_padder(nb_len, clipb);
	}
	if (flg_verif('0', flags) == 1 && minus == -1)
	{
		if ((flags->padding - flags->precision) > nb_len)
		{
			ft_zero_padder(nb_len, clipb);
		}
	}
	ft_write_wrap(buffer, (size_t)nb_len, clipb);
	if (minus == 1 && flags->padding > nb_len)
	{
		ft_space_padder(nb_len, clipb);
	}
}

static void				ft_unsigned_dec_prec(\
							const char *const buffer,\
							const unsigned short nb_len,\
							t_writer *const clipb)
{
	t_flag *const	flags = clipb->flags;
	const int		minus = flg_verif('-', flags);

	if (minus == -1 && flags->padding > nb_len)
	{
		ft_space_padder(nb_len, clipb);
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

static unsigned short	ft_int_len(char *const buffer,\
							const unsigned long long nb)
{
	unsigned long long	temp_num;
	unsigned short		num_len;
	unsigned short		cur_len;
	const char			base[] = "0123456789";

	temp_num = nb;
	num_len = ft_ull_len(nb, 10);
	cur_len = num_len - 1;
	while (temp_num >= 10)
	{
		buffer[cur_len] = base[(temp_num % 10)];
		temp_num /= 10;
		cur_len--;
	}
	buffer[cur_len] = base[temp_num];
	return (num_len);
}

int						ft_unsigned_dec(va_list args,\
							t_writer *const clipb)
{
	char				buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;
	const int			precision = flg_verif('.', clipb->flags);
	t_flag *const		flags = clipb->flags;

	ft_unsignconv(args, &nb, clipb->flags);
	if (!(nb == 0 && flags->padding == 0 && precision == 1))
	{
		nb_len = ft_int_len(buffer, nb);
		if (nb == 0 && flags->precision < nb_len && precision == 1)
		{
			ft_strcpy(buffer, " ");
		}
		if (precision == 1)
		{
			ft_unsigned_dec_prec(buffer, nb_len, clipb);
		}
		else
		{
			ft_unsigned_dec_noprec(buffer, nb_len, clipb);
		}
	}
	return (0);
}
