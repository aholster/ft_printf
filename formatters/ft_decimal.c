/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_decimal.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 12:06:16 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/03 17:52:35 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int				ft_preprint(const int is_neg,\
							t_writer *const restrict clipb)
{
	if (is_neg >= 0)
	{
		if (flagverif('+', clipb->flags) == 1)
		{
			if (clipb->self("+", 1, clipb) == -1)
				return (-1);
		}
		else if (flagverif(' ', clipb->flags) == 1)
		{
			if (clipb->self(" ", 1, clipb) == -1)
				return (-1);
		}
	}
	else if (is_neg < 0)
	{
		if (clipb->self("-", 1, clipb) == -1)
			return (-1);
	}
	return (1);
}

static int				ft_decimal_noprec(const char *const restrict buffer,\
							const int is_neg,\
							const unsigned short nb_len,\
							t_writer *const restrict clipb)
{
	int minus;

	minus = flagverif('-', clipb->flags);
	if (minus == -1 && flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (ft_preprint(is_neg, clipb) == -1)
		return (-1);
	if (flagverif('0', clipb->flags) == 1 && minus == -1)
	{
		if ((clipb->flags->padding - clipb->flags->precision) > nb_len)
		{
			if (ft_zero_padder(nb_len, clipb) == -1)
				return (-1);
		}
	}
	if (clipb->self(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (minus == 1 && clipb->flags->padding > nb_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_decimal_prec(const char *const restrict buffer,\
							const int is_neg,\
							unsigned short nb_len,\
							t_writer *const restrict clipb)
{
	int		minus;
	int		holder;
	uint	tru_len;

	tru_len = clipb->flags->precision;
	if (is_neg < 0)
		tru_len++;
	minus = flagverif('-', clipb->flags);
	if (minus == -1 && clipb->flags->padding > tru_len)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	holder = ft_preprint(is_neg, clipb);
	if (holder == -1)
		return (-1);
	if (clipb->flags->precision > nb_len)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->self(buffer, (size_t)nb_len, clipb) == -1)
		return (-1);
	if (minus == 1 && clipb->flags->padding > nb_len)
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

int						ft_decimal(va_list args, t_writer *const restrict clipb)
{
	char				buffer[20];
	unsigned long long	nb;
	unsigned short		nb_len;
	int					is_neg;
	int					precision;

	precision = flagverif('.', clipb->flags);
	is_neg = ft_signconv(args, &nb, clipb->flags);
	nb_len = ft_int_len(buffer, nb);
	if (nb == 0 && precision == 1 && clipb->flags->padding == 0)
		return (1);
	if (nb == 0 && precision == 1 && clipb->flags->precision < nb_len)
		ft_strcpy((char*)buffer, " ");
	if (clipb->flags->padding != 0 && (is_neg == -1 || \
	flagverif('+', clipb->flags) == 1 || flagverif(' ', clipb->flags) == 1))
		clipb->flags->padding -= 1;
	if (precision == 1)
		return (ft_decimal_prec(buffer, is_neg, nb_len, clipb));
	if (precision == -1)
		return (ft_decimal_noprec(buffer, is_neg, nb_len, clipb));
	return (1);
}
