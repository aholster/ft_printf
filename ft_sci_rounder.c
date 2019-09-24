/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sci_rounder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 17:42:52 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/23 14:29:28 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static size_t		ft_handle_nine(char *buffer, size_t len)
{
	if (buffer[len] < '9' && buffer[len] >= '0' && buffer[len] != '.')
	{
		buffer[len] = (int)(buffer[len] - '0') + '1';
		len--;
	}
	else if (buffer[len] == '9' && len != 1 && buffer[len] != '.')
	{
		buffer[len] = '0';
		len--;
	}
	else if (buffer[len] == '9' && len == 1)
	{
		buffer[len] = '1';
		len--;
	}
	if (buffer[len] == '.')
		len--;
	return (len);
}

static void			ft_sci_exception(char *buffer, size_t len)
{
	while (buffer[len] == '9')
	{
		len = ft_handle_nine(buffer, len);
	}
	if (buffer[len] == '.' && len > 1)
	{
		len--;
		buffer[len] = (buffer[len] - '0') + '1';
	}
	else if (buffer[len] >= '0' && buffer[len] < '9' && len > 1)
		buffer[len] = (buffer[len] - '0') + '1';
}

void				ft_sci_rounder(char *buffer, t_print *const restrict clipb, \
				size_t nb_len)
{
	unsigned int		precision;
	unsigned int		rounding_num;
	size_t				len;

	len = 0;
	precision = clipb->flags->precision;
	rounding_num = buffer[nb_len - 1] - '0';
	while (buffer[len] != '.')
		len++;
	len += precision + 1;
	if (rounding_num > 5)
	{
		if (buffer[len] == '9')
		{
			ft_sci_exception(buffer, len);
		}
		else if (buffer[len] >= '0' && buffer[len] < '9' && buffer[len] != '.')
		{
			len--;
			if (buffer[len] == '.')
				len--;
			buffer[len] = (buffer[len] - '0') + '1';
		}
	}
}

size_t				ft_expon_rounding(char *buffer, size_t nb_len, \
				t_print *const restrict clipb)
{
	size_t			index;
	size_t			rounded;
	unsigned int	precision;

	index = 0;
	rounded = 0;
	precision = clipb->flags->precision;
	while (buffer[index] != '.' && index < nb_len)
		index++;
	if (buffer[index] == '.')
	{
		if (buffer[index + 1] == '9' && buffer[index - 1] == '9')
			rounded++;
	}
	return (rounded);
}