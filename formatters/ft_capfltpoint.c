/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_capfltpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/09 13:45:51 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/04 17:59:00 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int		ft_offset_handler(char *restrict *const restrict buffer,\
					t_writer *const restrict clipb,\
					const size_t offset)
{
	if (offset == 0)
	{
		if (clipb->self(*buffer, 1, clipb) == -1)
			return (-1);
		*buffer += 1;
	}
	return (1);
}

static int		ft_float_print(const char *const restrict buffer,\
					t_writer *const restrict clipb,\
					size_t nb_len,\
					const size_t offset)
{
	if (offset == 0)
		nb_len--;
	if (clipb->self(buffer, nb_len, clipb) == -1)
		return (-1);
	if (offset == 0)
		nb_len++;
	if (flg_verif('-', clipb->flags) == 1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static int		ft_float_padding(char *restrict buffer,\
					t_writer *const restrict clipb,\
					size_t nb_len,\
					const int is_neg)
{
	t_flag *const restrict	flags = clipb->flags;
	size_t					offset;

	offset = ft_x_offset(&buffer, &nb_len, flags, is_neg);
	if (flg_verif('-', flags) == -1 && \
		flg_verif('0', flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (ft_offset_handler(&buffer, clipb, offset) == -1)
		return (-1);
	if (flg_verif('-', flags) == -1 && \
		flg_verif('0', flags) == 1)
	{
		if (flags->precision == 6)
			flags->padding += flags->precision;
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	}
	if (ft_float_print(buffer, clipb, nb_len, offset) == -1)
		return (-1);
	return (1);
}

static int		ft_float_prep(char *const restrict buffer,\
					size_t nb_len,\
					t_writer *const restrict clipb,\
					const int is_neg)
{
	int ret_hold;

	if (clipb->flags->precision == 0)
		nb_len--;
	ft_float_rounder(buffer, clipb->flags, &nb_len);
	nb_len--;
	ret_hold = ft_float_padding(buffer, clipb, nb_len, is_neg);
	return (ret_hold);
}

int				ft_capfltpoint(va_list args, t_writer *const restrict clipb)
{
	char			*buffer;
	long double		nb;
	size_t			nb_len;
	int				is_neg;
	int				ret_hold;

	is_neg = ft_longdouble_conv(args, &nb, clipb->flags);
	if (flg_verif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	if (ft_custom_ld_to_text(nb, \
		clipb->flags->precision, &buffer, &nb_len) == -1)
		return (-1);
	if (ft_memcmp(buffer, "nan", nb_len) == 0\
	|| ft_memcmp(buffer, "inf", nb_len) == 0)
	{
		ft_captolow(buffer);
		ret_hold = ft_naninf_padding(buffer, clipb, nb_len, is_neg);
	}
	else
		ret_hold = ft_float_prep(buffer, nb_len, clipb, is_neg);
	free(buffer);
	return (ret_hold);
}
