/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowshrthd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/21 12:57:35 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/24 12:41:51 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"
#include <stdio.h>

static size_t		ft_x_offset(char *buffer, size_t *nb_len, \
				t_print *const restrict clipb, int neg)
{
	size_t offset;

	offset = 0;
	if (buffer[0] == 'X')
	{
		if (neg == 1)
		{
			if (flagverif('+', clipb->flags) == 1)
				buffer[0] = '+';
			else if (flagverif(' ', clipb->flags) == 1)
				buffer[0] = ' ';
			else if (flagverif('+', clipb->flags) == -1 && flagverif(' ', clipb->flags) == -1)
			{
				offset++;
				*nb_len -= 1;
			}
		}
		else
			buffer[0] = '-';
		*nb_len += 1;
	}
	return (offset);
}

static void		ft_expon_len(char *buffer, size_t *new_len, t_print *const restrict clipb)
{
	size_t 			index;
	size_t			holder;
	unsigned int	precision;

	index = 0;
	precision = clipb->flags->precision;
	while (buffer[index] !='.')
		index++;
	index++;
	if (buffer[index] == '.' && precision == index)
		index--;
	if (precision > index)
	{
		holder = precision - index;
		*new_len = index + holder + 1;
	}
	else if (precision == index)
		*new_len = index;
	else if (precision < index && precision != 0)
		*new_len = index;
	else if (precision == 0)
		*new_len = 7;
	*new_len -= 2;
	// return (new_len);
}

static size_t		ft_shorthand_prec(char *buffer, \
				size_t nb_len, t_print *const restrict clipb)
{
	size_t			index;
	size_t			holder;
	size_t			new_len;
	unsigned int	precision;

	new_len = nb_len;
	precision = clipb->flags->precision;
	ft_expon_len(buffer, &new_len, clipb);
	ft_shrthd_rounder(buffer, clipb, new_len);
	index = new_len;
	while (buffer[index] == '0' && buffer[index] != '.')
	{
		holder = index;
		index--;
	}
	if (buffer[index] == '.')
		index--;
	return (index);
}

static int			ft_shrthd_padding(char *buffer, \
				size_t offset, t_print *const clipb, size_t new_len)
{
	size_t diff;

	//printf("\nnew_len: %zu\n", new_len);
	diff = 7 - new_len;
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(new_len, clipb) == -1)
			return (-1);
	if (offset == 0)
	{
		if (clipb->printer(buffer, 1, clipb) == -1)
			return (-1);
		buffer = buffer + 1;
		diff++;
	}
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == 1 && clipb->flags->padding > new_len)
		if (pad_zero(clipb->flags->padding - new_len, clipb) == -1)
			return (-1);
	if (offset == 0)
		new_len--;
	if (flagverif('#', clipb->flags) == 1 && new_len < 7)
	{
		if (clipb->printer(buffer + offset, new_len + diff, clipb) == -1)
			return (-1);
		new_len += diff;
	}
	else 
		if (clipb->printer(buffer + offset, new_len, clipb) == -1)
			return (-1);
	if (offset == 0)
		new_len++;
	if (flagverif('-', clipb->flags) == 1)
		if (ft_space_padder(new_len, clipb) == -1)
			return (-1);
	return (1);
}

static int		ft_lowsci_prep(char *buffer, t_print *const restrict clipb, int neg, size_t nb_len)
{
	size_t				offset;
	size_t				new_len;
	int					ret_val;

	new_len = ft_shorthand_prec(buffer, nb_len, clipb);
	offset = ft_x_offset(buffer, &new_len, clipb, neg);
	// printf("new: %zu\n", new_len);
	if (new_len > clipb->flags->precision)
		clipb->flags->precision = new_len - clipb->flags->precision;
	else 
		clipb->flags->precision = new_len;
	// if (new_len )
	ret_val = ft_shrthd_padding(buffer, offset, clipb, new_len);
	free(buffer);
	return (ret_val);
}

static int				ft_which_one(char *buffer, t_print *const restrict clipb, size_t nb_len, long double nb)
{
	size_t	sci_note;
	size_t	float_note;
	int		ret_val;

	sci_note = 7;
	float_note = ft_shorthand_prec(buffer, nb_len, clipb);
	if (sci_note < float_note)
	{
		printf("here\n");
		ret_val = ft_shrthd_lowsci(buffer, clipb, nb, nb_len);
		free(buffer);
		return (ret_val);
	}
	return (0);
}

int					ft_lowshrthd(va_list args, t_print *const restrict clipb)
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
	ret_val = ft_which_one(buffer, clipb, nb_len, nb);
	if (ret_val == -1 || ret_val == 1)
		return (ret_val);
	else
		return (ft_lowsci_prep(buffer, clipb, neg, nb_len));
}
