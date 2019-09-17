/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rounder.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 10:14:39 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/17 21:28:40 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t		ft_handling_nine(char *const restrict buffer, size_t len)
{
	if (buffer[len] == '9' && buffer[len - 1] != '.' && len > 1)
		buffer[len] = '0';
	else if (buffer[len] != '9' && buffer[len - 1] != '.')
		buffer[len] = (int)(buffer[len] - '0') + '1';
	else if (buffer[len] == '9' && buffer[len - 1] == '.')
	{
		buffer[len] = '.';
		len--;
		if (buffer[len - 1] != '9')
			buffer[len] = (int)(buffer[len - 1] - '0') + '1';
		else
			buffer[len] = '0';
	}
	else if ((buffer[len] == '9' && len == 1) || buffer[len] == 'X')
		buffer[len] = '1';
	else if (buffer[len] < '9' && buffer[len] != '.')
		buffer[len] = (buffer[len] - '0') + '1';
	len--;
	return (len);
}

static void			ft_rounder_exception(char *const restrict buffer,\
										size_t len)
{
	while (buffer[len] == '9')
		len = ft_handling_nine(buffer, len);
	if (buffer[len] == '.')
	{
		len--;
		buffer[len] = (buffer[len] - '0') + '1';
	}
	else
		buffer[len] = (buffer[len] - '0') + '1';
}

void				ft_rounder(t_float conversion, char *const restrict buffer,\
					t_print *const restrict clipb, size_t nb_len)
{
	unsigned int		precision;
	unsigned int		rounding_num;
	size_t				len;

	len = 0;
	(void)conversion;
	precision = clipb->flags->precision;
	rounding_num = buffer[nb_len - 1] - '0';
	while (buffer[len] != '.')
		len++;
	len += precision + 2;
	if (rounding_num > 5)
	{
		len--;
		if (buffer[len] == '9')
			ft_rounder_exception(buffer, len);
		else if (buffer[len] >= '0' && buffer[len] < '9' && buffer[len] != '.')
		{
			len--;
			buffer[len] = (buffer[len] - '0') + '1';
		}
	}
}
