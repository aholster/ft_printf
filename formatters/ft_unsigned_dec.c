/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsigned_dec.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 19:12:27 by aholster       #+#    #+#                */
/*   Updated: 2019/10/04 17:57:45 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int				ft_unsigned_dec_noprec(\
							const char *const restrict buffer,\
							const unsigned short nb_len,\
							t_writer *const restrict clipb)
{
	t_flag *const restrict	flags = clipb->flags;
	const int				minus = flg_verif('-', flags);

	if (minus == -1 && flg_verif('0', flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (flg_verif('0', flags) == 1 && minus == -1)
	{
		if ((flags->padding - flags->precision) > nb_len)
		{
			if (ft_zero_padder(nb_len, clipb) == -1)
				return (-1);
		}
	}
	if (clipb->self(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (minus == 1 && flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_unsigned_dec_prec(\
							const char *const restrict buffer,\
							const unsigned short nb_len,\
							t_writer *const restrict clipb)
{
	t_flag *const restrict	flags = clipb->flags;
	const int				minus = flg_verif('-', flags);

	if (minus == -1 && flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (flags->precision > nb_len)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->self(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (minus == 1 && flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static unsigned short	ft_int_len(char *const restrict buffer,\
							const unsigned long long nb)
{
	unsigned long long			temp_num;
	unsigned short				num_len;
	unsigned short				cur_len;
	const char *const restrict	base = "0123456789";

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
							t_writer *const restrict clipb)
{
	char					buffer[20];
	unsigned long long		nb;
	unsigned short			nb_len;
	const int				precision = flg_verif('.', clipb->flags);
	t_flag *const restrict	flags = clipb->flags;

	ft_unsignconv(args, &nb, clipb->flags);
	nb_len = ft_int_len(buffer, nb);
	if (nb == 0 && flags->padding == 0 && precision == 1)
		return (1);
	if (nb == 0 && flags->precision < nb_len && precision == 1)
		ft_strcpy(buffer, " ");
	if (precision == 1)
		return (ft_unsigned_dec_prec(buffer, nb_len, clipb));
	else
		return (ft_unsigned_dec_noprec(buffer, nb_len, clipb));
	return (1);
}
