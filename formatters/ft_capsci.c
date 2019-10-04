/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_capsci.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/21 11:16:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/04 17:53:02 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int		ft_capsci_buffer(char *const restrict buffer,\
					t_writer *const restrict clipb,\
					size_t nb_len,\
					const short expon)
{
	t_flag *const restrict	flags = clipb->flags;
	int						ret_val;
	int						temp;
	size_t					round_len;

	temp = expon;
	nb_len = flags->precision + 3;
	if (buffer[nb_len] == '.')
		nb_len--;
	round_len = nb_len + 1;
	ft_sci_rounder(buffer, clipb->flags, &round_len);
	if (flags->precision == 0)
		nb_len--;
	ret_val = ft_capsci_print(buffer, nb_len, clipb, expon);
	return (ret_val);
}

static int		ft_naninf_print(char *const restrict buffer,\
					t_writer *const restrict clipb,\
					size_t nb_len)
{
	int ret_val;
	int is_neg;

	is_neg = 1;
	if (buffer[0] == '-')
		is_neg = -1;
	ft_captolow(buffer);
	ret_val = ft_naninf_padding(buffer, clipb, nb_len, is_neg);
	return (ret_val);
}

int				ft_capsci(va_list args, t_writer *const restrict clipb)
{
	char			*buffer;
	long double		nb;
	size_t			nb_len;
	int				ret_val;
	short			expon;

	ret_val = ft_longdouble_conv(args, &nb, clipb->flags);
	if (flg_verif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	if (ft_custom_ld_to_text(nb, \
	clipb->flags->precision, &buffer, &nb_len) == -1)
		return (-1);
	if (ret_val == -1)
		buffer[0] = '-';
	if (ft_memcmp(buffer, "nan", nb_len) == 0\
	|| ft_memcmp(buffer, "inf", nb_len) == 0)
		ret_val = ft_naninf_print(buffer, clipb, nb_len);
	else
	{
		expon = ft_expon_finder(buffer, nb_len);
		expon += ft_expon_rounding(buffer, nb_len, clipb->flags, expon);
		ret_val = ft_capsci_buffer(buffer, clipb, nb_len, expon);
	}
	free(buffer);
	return (ret_val);
}
