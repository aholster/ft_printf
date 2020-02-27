/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowsci.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 11:15:26 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 11:46:31 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static void		ft_lowsci_buffer(char *buffer,\
					t_writer *const clipb,\
					size_t nb_len,\
					const short expon)
{
	t_flag *const	flags = clipb->flags;
	size_t			round_len;

	nb_len = flags->precision + 3;
	if (buffer[nb_len] == '.')
	{
		nb_len--;
	}
	round_len = nb_len + 1;
	ft_sci_rounder(buffer, clipb->flags, &round_len);
	if (flags->precision == 0)
	{
		nb_len--;
	}
	ft_lowsci_print(buffer, nb_len, clipb, expon);
}

static void		ft_naninf_print(char *buffer,\
					t_writer *const clipb,\
					size_t nb_len)
{
	int is_neg;

	is_neg = 1;
	if (buffer[0] == '-')
	{
		is_neg = -1;
	}
	ft_naninf_padding(buffer, clipb, nb_len, is_neg);
}

int				ft_lowsci(va_list args, t_writer *const clipb)
{
	char				*buffer;
	long double			nb;
	size_t				nb_len;
	short				expon;
	int const			is_neg = ft_longdouble_conv(args, &nb, clipb->flags);

	if (flg_verif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	if (ft_custom_ld_to_text(nb, \
		clipb->flags->precision, &buffer, &nb_len) == -1)
		return (-1);
	if (is_neg == -1)
		buffer[0] = '-';
	if (ft_memcmp(buffer, "nan", nb_len) == 0\
		|| ft_memcmp(buffer, "inf", nb_len) == 0)
		ft_naninf_print(buffer, clipb, nb_len);
	else
	{
		expon = ft_expon_finder(buffer, nb_len);
		expon += ft_expon_rounding(buffer, nb_len, clipb->flags, expon);
		ft_lowsci_buffer(buffer, clipb, nb_len, expon);
	}
	free(buffer);
	return (0);
}
