/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_capshrthd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/27 11:34:23 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/30 12:21:22 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static int			ft_print_prep(char *buffer, \
				t_print *const restrict clipb, int neg, size_t new_len)
{
	size_t				offset;
	int					ret_val;

	offset = ft_shrthd_offset(&buffer, &new_len, clipb, neg);
	if (new_len > clipb->flags->precision)
		clipb->flags->precision = new_len - clipb->flags->precision;
	else
		clipb->flags->precision = new_len;
	if (offset == 0)
	{
		if (clipb->flags->precision > 0)
			clipb->flags->precision -= 1;
		if (clipb->flags->padding > 0)
			clipb->flags->padding -= 1;
	}
	if (buffer[new_len] == '.' && clipb->flags->precision < new_len)
		new_len--;
	ret_val = ft_shrthd_print(buffer, offset, clipb, new_len);
	return (ret_val);
}

static size_t		ft_shorthand_prec(char *buffer, \
				size_t nb_len, t_print *const restrict clipb, int neg)
{
	size_t			index;
	size_t			holder;
	size_t			new_len;
	int				decimal;
	unsigned int	precision;

	new_len = nb_len;
	decimal = 0;
	precision = clipb->flags->precision;
	ft_expon_len(buffer, &new_len, clipb, neg);
	ft_shrthd_rounder(buffer, clipb, new_len);
	index = new_len;
	if (buffer[index] == '.')
		index--;
	while (buffer[index] == '0')
	{
		holder = index;
		index--;
		if (buffer[index] == '.')
			index--;
	}
	if (index == 0)
		index++;
	return (index);
}

static int			ft_shrthd_capsci(char *buffer, \
				t_print *const restrict clipb, size_t nb_len)
{
	int					expon;
	int					ret_val;

	expon = ft_expon_finder(buffer, nb_len);
	ft_sci_rounder(buffer, clipb, nb_len);
	if (flagverif('.', clipb->flags) == -1)
		nb_len -= 1;
	if (buffer[nb_len] == '.')
		nb_len--;
	expon += ft_expon_rounding(buffer, nb_len, clipb);
	if (flagverif('.', clipb->flags) == 1)
		nb_len -= 1;
	if (buffer[nb_len - 1] == '.')
		nb_len--;
	ret_val = ft_capsci_print(buffer, nb_len, clipb, expon);
	return (ret_val);
}

static int			ft_which_one(char *buffer, t_print *const restrict clipb, \
			size_t nb_len)
{
	size_t	sci_note;
	size_t	expon_len;
	size_t	new_len;
	int		ret_val;
	int		neg;

	neg = 1;
	sci_note = clipb->flags->precision + 1;
	expon_len = 0;
	if (buffer[0] == '-')
		neg = -1;
	buffer[0] = 'X';
	while (buffer[expon_len] != '.')
		expon_len++;
	if (sci_note < expon_len)
	{
		new_len = clipb->flags->precision + 3;
		if (clipb->flags->precision != 0)
			clipb->flags->precision -= 1;
		ret_val = ft_shrthd_capsci(buffer, clipb, new_len);
		return (ret_val);
	}
	new_len = ft_shorthand_prec(buffer, nb_len, clipb, neg);
	ret_val = ft_print_prep(buffer, clipb, neg, new_len);
	return (ret_val);
}

int					ft_capshrthd(va_list args, t_print *const restrict clipb)
{
	char				*buffer;
	long double			nb;
	size_t				nb_len;
	int					neg;
	int					ret_val;

	neg = ft_longdouble_conv(args, &nb, clipb->flags);
	if (flagverif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	if (ft_custom_ld_to_text(nb, \
	clipb->flags->precision, &buffer, &nb_len) == -1)
		return (-1);
	if (ft_strcmp(buffer, "nan") == 0 || ft_strcmp(buffer, "inf") == 0)
	{
		ft_captolow(buffer);
		ret_val = ft_naninf_padding(buffer, clipb, nb_len);
	}
	else
	{
		if (neg == -1)
			buffer[0] = '-';
		ret_val = ft_which_one(buffer, clipb, nb_len);
	}
	free(buffer);
	return (ret_val);
}
