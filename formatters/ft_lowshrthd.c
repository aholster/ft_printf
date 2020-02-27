/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowshrthd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/21 12:57:35 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 11:51:22 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static void			ft_print_prep(char *buffer,\
						t_writer *const clipb,\
						const int is_neg,\
						size_t new_len)
{
	t_flag *const	flags = clipb->flags;
	size_t			offset;

	offset = ft_shrthd_offset(&buffer, clipb, is_neg);
	if (new_len > flags->precision)
		flags->precision = new_len - flags->precision;
	else
		flags->precision = new_len;
	if (offset == 0)
	{
		if (flags->precision > 0)
			flags->precision -= 1;
		if (flags->padding > 0)
			flags->padding -= 1;
	}
	if (buffer[new_len] == '.' && flags->precision < new_len)
		new_len--;
	ft_shrthd_print(buffer, offset, clipb, new_len);
}

static size_t		ft_shorthand_prec(char *buffer,\
						size_t nb_len,\
						t_writer *const clipb)
{
	size_t			index;
	size_t			holder;
	size_t			new_len;
	int				decimal;
	unsigned int	precision;

	new_len = nb_len;
	decimal = 0;
	precision = clipb->flags->precision;
	ft_expon_len(buffer, &new_len, clipb);
	ft_shrthd_rounder(buffer, clipb->flags, &new_len);
	index = new_len;
	if (buffer[index] == '.')
		index--;
	while (buffer[index] == '0')
	{
		holder = index;
		index--;
		if (buffer[index] == '.' && buffer[index - 1] != '0')
			index--;
	}
	if (index == 0)
		index++;
	return (index);
}

static void			ft_shrthd_lowsci(char *buffer, \
						t_writer *const clipb,\
						size_t nb_len)
{
	int					expon;

	expon = ft_expon_finder(buffer, nb_len);
	ft_sci_rounder(buffer, clipb->flags, &nb_len);
	if (flg_verif('.', clipb->flags) == -1)
		nb_len -= 1;
	if (buffer[nb_len] == '.')
		nb_len--;
	expon += ft_expon_rounding(buffer, nb_len, clipb->flags, expon);
	if (flg_verif('.', clipb->flags) == 1)
		nb_len -= 1;
	if (buffer[nb_len - 1] == '.')
		nb_len--;
	ft_lowsci_print(buffer, nb_len, clipb, expon);
}

static void			ft_which_one(char *buffer,\
						t_writer *clipb,\
						size_t nb_len)
{
	size_t	sci_note;
	size_t	expon_len;
	size_t	new_len;
	int		is_neg;

	is_neg = 1;
	sci_note = clipb->flags->precision + 2;
	expon_len = 0;
	if (buffer[0] == '-')
		is_neg = -1;
	while (buffer[expon_len] != '.')
		expon_len++;
	if (sci_note < expon_len)
	{
		new_len = clipb->flags->precision + 3;
		if (clipb->flags->precision != 0)
			clipb->flags->precision -= 1;
		ft_shrthd_lowsci(buffer, clipb, new_len);
	}
	else
	{
		new_len = ft_shorthand_prec(buffer, nb_len, clipb);
		ft_print_prep(buffer, clipb, is_neg, new_len);
	}
}

int					ft_lowshrthd(va_list args, t_writer *const clipb)
{
	char				*buffer;
	long double			nb;
	size_t				nb_len;
	int const			is_neg = ft_longdouble_conv(args, &nb, clipb->flags);

	if (flg_verif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	if (ft_custom_ld_to_text(nb, \
		clipb->flags->precision, &buffer, &nb_len) == -1)
	{
		return (-1);
	}
	if (is_neg == -1)
		buffer[0] = '-';
	ft_which_one(buffer, clipb, nb_len);
	free(buffer);
	return (0);
}
