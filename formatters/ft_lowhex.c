/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowhex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 16:34:02 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/04 17:55:25 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int				ft_lowhex_noprec(const char *const restrict buffer,\
							const unsigned long long nb,\
							const unsigned short nb_len,\
							t_writer *const restrict clipb)
{
	t_flag *const restrict	flags = clipb->flags;
	const int				minus = flg_verif('-', flags);

	if (minus == -1 && flg_verif('0', flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (flg_verif('#', flags) == 1 && nb != 0)
		if (clipb->self("0x", 2, clipb) == -1)
			return (-1);
	if (flg_verif('0', flags) == 1 && minus == -1)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->self(buffer, ((size_t)nb_len), clipb) == -1)
		return (-1);
	if (minus == 1 && flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_lowhex_prec(const char *const restrict buffer,\
							const unsigned long long nb,\
							const unsigned short nb_len,\
							t_writer *const restrict clipb)
{
	t_flag *const restrict	flags = clipb->flags;
	const int				minus = flg_verif('-', flags);

	if (minus == -1 && flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (flg_verif('#', flags) == 1 && nb != 0)
		if (clipb->self("0x", 2, clipb) == -1)
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

static unsigned short	ull_to_hex(char *const restrict buffer,\
							unsigned long long nb)
{
	unsigned short				index;
	unsigned short				len;
	const char *const restrict	base = "0123456789abcdef";
	unsigned long long			tempnum;

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

int						ft_lowhex(va_list args, t_writer *const restrict clipb)
{
	char					buffer[20];
	unsigned long long		nb;
	unsigned short			nb_len;
	int						precision;
	t_flag *const restrict	flags = clipb->flags;

	precision = flg_verif('.', flags);
	ft_unsignconv(args, &nb, flags);
	nb_len = ull_to_hex(buffer, nb);
	if (flg_verif('#', clipb->flags) == 1 && nb != 0 && \
		flags->padding >= 2)
		flags->padding -= 2;
	if (nb == 0 && precision == 1)
	{
		if (flags->padding == 0)
			return (1);
		if (flags->precision == 0)
			ft_strcpy(buffer, " ");
	}
	if (precision == 1)
		return (ft_lowhex_prec(buffer, nb, nb_len, clipb));
	else
		return (ft_lowhex_noprec(buffer, nb, nb_len, clipb));
	return (1);
}
