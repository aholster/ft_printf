/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_octal.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 15:08:26 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 10:14:07 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static void				ft_octal_noprec(const char *const buffer,\
							const unsigned short nb_len,\
							t_writer *const clipb)
{
	t_flag *const	flags = clipb->flags;
	const int		minus = flg_verif('-', flags);

	if (minus == -1 && flg_verif('0', flags) == -1 && flags->padding > 0)
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

static void				ft_octal_prec(const char *const buffer,\
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
							const unsigned long long nb,\
							t_writer *const clipb)
{
	unsigned long long	temp_num;
	unsigned short		num_len;
	unsigned short		cur_len;
	const char			base[] = "01234567";

	temp_num = nb;
	num_len = ft_ull_len(nb, 8);
	cur_len = num_len - 1;
	if (flg_verif('#', clipb->flags) == 1 && nb != 0)
	{
		cur_len++;
		buffer[0] = '0';
		num_len++;
	}
	while (temp_num >= 8)
	{
		buffer[cur_len] = base[(temp_num % 8)];
		temp_num /= 8;
		cur_len--;
	}
	buffer[cur_len] = base[temp_num];
	return (num_len);
}

int						ft_octal(va_list args, t_writer *const clipb)
{
	char				buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;
	int const			prec = flg_verif('.', clipb->flags);
	int const			exten = flg_verif('#', clipb->flags);

	ft_unsignconv(args, &nb, clipb->flags);
	if (!(exten == -1 && prec == 1 && nb == 0 && clipb->flags->padding == 0))
	{
		nb_len = ft_int_len(buffer, nb, clipb);
		if (exten == -1 && prec == 1 && nb == 0 &&\
			clipb->flags->precision == 0)
		{
			ft_strcpy((char*)buffer, " ");
		}
		if (prec == 1)
		{
			ft_octal_prec(buffer, nb_len, clipb);
		}
		else
		{
			ft_octal_noprec(buffer, nb_len, clipb);
		}
	}
	return (0);
}
