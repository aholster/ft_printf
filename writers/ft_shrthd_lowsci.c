/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shrthd_lowsci.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/23 14:15:42 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/23 16:39:59 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"
#include <stdio.h>
static size_t			ft_expon_prefix(char *buffer, int expon)
{
	size_t index;

	index = 2;
	buffer[0] = 'e';
	if (expon < 0)
		buffer[1] = '-';
	else 
		buffer[1] = '+';
	if (expon < 0)
		expon *= -1;
	if (expon == 0)
	{
		buffer[index] = '0';
		index++;
	}
	if (expon < 10)
	{
		buffer[index] = '0';
		index++;
	}
	return (index);
}

static int				ft_expon_to_buf(int expon, t_print *const clipb)
{
	char	buffer[10];
	size_t	index;

	index = ft_expon_prefix(buffer, expon);
	if (expon < 0)
		expon *= -1;
	while (expon > 0)
	{
		buffer[index] = expon % 10 + '0';
		index++;
		expon /= 10;
	}
	if (clipb->printer(buffer, index, clipb) == -1)
		return (-1);
	return (1);
}

static size_t 			ft_scix_offset(char *buffer, size_t *nb_len, \
					t_print *const restrict clipb)
{
	size_t offset;

	offset = 0;
	if (buffer[0] == 'X')
	{
		{
			if (flagverif('+', clipb->flags) == 1)
				buffer[0] = '+';
			else if (flagverif(' ', clipb->flags) == 1 && \
			flagverif('+', clipb->flags) == -1)
				buffer[0] = ' ';
			else if (flagverif('+', clipb->flags) == -1 \
			&& flagverif(' ', clipb->flags) == -1)
			{
				offset++;
				*nb_len -= 1;
			}
		}
	}
	return (offset);
}

static int				ft_lowsci_pos(char *buffer, \
					size_t nb_len, t_print *const clipb, int expon)
{
	size_t	len_extension;
	size_t	offset;

	offset = ft_scix_offset(buffer, &nb_len, clipb);
	nb_len = nb_len - expon - offset;
	len_extension = ft_nbrlen((long long)expon, 10) + nb_len + 2;
	if (clipb->flags->precision == 0)
		nb_len--;
	if (expon > 0)
		len_extension++;
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(len_extension, clipb) == -1)
			return (-1);
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == 1)
		if (ft_zero_padder(len_extension, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer + offset, nb_len, clipb) == -1) 
		return (-1);
	if (ft_expon_to_buf(expon, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > nb_len)
		if (ft_space_padder(len_extension, clipb) == -1)
			return (-1);
	return (1);
}

int						ft_shrthd_lowsci(char *buffer, \
					t_print *const restrict clipb, long double nb, short nb_len)
{
	int					expon;
	int					ret_val;

	expon = ft_float_expon_math(&nb);
	// printf("nb: %Lf\n", nb);
	// printf("buffer: %s\n", buffer);
	if (nb < 0)
		buffer[0] = '-';
	expon += ft_expon_rounding(buffer, nb_len, clipb);
	ft_sci_rounder(buffer, clipb, nb_len);
	nb_len--;
	ret_val = ft_lowsci_pos(buffer, nb_len, clipb, expon);
	free(buffer);
	return (ret_val);
}