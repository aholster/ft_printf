/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_capfltpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/09 13:45:51 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 11:10:19 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static void		ft_offset_handler(char **const buffer,\
					t_writer *const clipb,\
					const size_t offset)
{
	if (offset == 0)
	{
		ft_write_wrap(*buffer, 1, clipb);
		*buffer += 1;
	}
}

static void		ft_float_print(const char *const buffer,\
					t_writer *const clipb,\
					size_t nb_len,\
					const size_t offset)
{
	if (offset == 0)
	{
		nb_len--;
	}
	ft_write_wrap(buffer, nb_len, clipb);
	if (offset == 0)
	{
		nb_len++;
	}
	if (flg_verif('-', clipb->flags) == 1)
	{
		ft_space_padder(nb_len, clipb);
	}
}

static void		ft_float_padding(char *buffer,\
					t_writer *const clipb,\
					size_t nb_len,\
					const int is_neg)
{
	t_flag *const	flags = clipb->flags;
	size_t			offset;

	offset = ft_x_offset(&buffer, &nb_len, flags, is_neg);
	if (flg_verif('-', flags) == -1 && \
		flg_verif('0', flags) == -1)
	{
		ft_space_padder(nb_len, clipb);
	}
	ft_offset_handler(&buffer, clipb, offset);
	if (flg_verif('-', flags) == -1 && \
		flg_verif('0', flags) == 1)
	{
		if (flags->precision == 6)
			flags->padding += flags->precision;
		ft_zero_padder(nb_len, clipb);
	}
	ft_float_print(buffer, clipb, nb_len, offset);
}

static void		ft_float_prep(char *const buffer,\
					size_t nb_len,\
					t_writer *const clipb,\
					const int is_neg)
{
	if (clipb->flags->precision == 0)
	{
		nb_len--;
	}
	ft_float_rounder(buffer, clipb->flags, &nb_len);
	nb_len--;
	ft_float_padding(buffer, clipb, nb_len, is_neg);
}

int				ft_capfltpoint(va_list args, t_writer *const clipb)
{
	char			*buffer;
	long double		nb;
	size_t			nb_len;
	int const		is_neg = ft_longdouble_conv(args, &nb, clipb->flags);

	if (flg_verif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	if (ft_custom_ld_to_text(nb, \
		clipb->flags->precision, &buffer, &nb_len) == -1)
		return (-1);
	if (ft_memcmp(buffer, "nan", nb_len) == 0\
		|| ft_memcmp(buffer, "inf", nb_len) == 0)
	{
		ft_captolow(buffer);
		ft_naninf_padding(buffer, clipb, nb_len, is_neg);
	}
	else
	{
		ft_float_prep(buffer, nb_len, clipb, is_neg);
	}
	free(buffer);
	return (0);
}
