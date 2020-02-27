/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_decimal.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 12:06:16 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 09:44:19 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static void				ft_preprint(const int is_neg,\
							t_writer *const clipb)
{
	if (is_neg >= 0)
	{
		if (flg_verif('+', clipb->flags) == 1)
		{
			ft_write_wrap("+", 1, clipb);
		}
		else if (flg_verif(' ', clipb->flags) == 1)
		{
			ft_write_wrap(" ", 1, clipb);
		}
	}
	else if (is_neg < 0)
	{
		ft_write_wrap("-", 1, clipb);
	}
}

static void				ft_decimal_noprec(const char *const buffer,\
							const int is_neg,\
							const unsigned short nb_len,\
							t_writer *const clipb)
{
	int				minus;
	t_flag *const	flags = clipb->flags;

	minus = flg_verif('-', flags);
	if (minus == -1 && flg_verif('0', flags) == -1)
	{
		ft_space_padder(nb_len, clipb);
	}
	ft_preprint(is_neg, clipb);
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

static void				ft_decimal_prec(const char *const buffer,\
							const int is_neg,\
							unsigned short nb_len,\
							t_writer *const clipb)
{
	int		minus;
	uint	tru_len;

	tru_len = clipb->flags->precision;
	if (is_neg < 0)
	{
		tru_len++;
	}
	minus = flg_verif('-', clipb->flags);
	if (minus == -1 && clipb->flags->padding > tru_len)
	{
		ft_space_padder(nb_len, clipb);
	}
	ft_preprint(is_neg, clipb);
	if (clipb->flags->precision > nb_len)
	{
		ft_zero_padder(nb_len, clipb);
	}
	ft_write_wrap(buffer, (size_t)nb_len, clipb);
	if (minus == 1 && clipb->flags->padding > nb_len)
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

int						ft_decimal(va_list args, t_writer *const clipb)
{
	char				buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;
	int const			is_neg = ft_signconv(args, &nb, clipb->flags);
	int const			is_precision = flg_verif('.', clipb->flags);

	nb_len = ft_int_len(buffer, nb);
	if (!(nb == 0 && is_precision == 1 &&\
		clipb->flags->precision == 0 && clipb->flags->padding == 0))
	{
		if (nb == 0 && is_precision == 1 && clipb->flags->precision < nb_len)
		{
			ft_strcpy((char*)buffer, " ");
		}
		if (clipb->flags->padding != 0 && (is_neg == -1 ||\
	flg_verif('+', clipb->flags) == 1 || flg_verif(' ', clipb->flags) == 1))
		{
			clipb->flags->padding -= 1;
		}
		if (is_precision == 1)
			ft_decimal_prec(buffer, is_neg, nb_len, clipb);
		else
			ft_decimal_noprec(buffer, is_neg, nb_len, clipb);
	}
	return (0);
}
