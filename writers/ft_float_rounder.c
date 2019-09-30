/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_float_rounder.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 10:14:39 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/30 12:19:09 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

static size_t		ft_handling_nine(char *buffer, size_t len)
{
	if (buffer[len] == '9' && buffer[len - 1] != '.' && len > 1)
		buffer[len] = '0';
	else if (buffer[len] != '9' && buffer[len - 1] != '.')
		buffer[len] = (buffer[len] - '0') + '1';
	else if (buffer[len] == '9' && buffer[len - 1] == '.')
	{
		if (len == 2)
		{
			buffer[len] = '.';
			len--;
		}
		if (buffer[len - 1] != '9' && buffer[len] >= '0' \
		&& buffer[len - 1] != '.')
			buffer[len] = (buffer[len - 1] - '0') + '1';
		else
			buffer[len] = '0';
	}
	else if ((buffer[len] == '9' && len == 0) || buffer[len] == 'X')
		buffer[len] = '1';
	else if (buffer[len] >= '0' && buffer[len] < '9' && buffer[len] != '.')
		buffer[len] = (buffer[len] - '0') + '1';
	len--;
	return (len);
}

static void			ft_rounder_exception(char *buffer, size_t len)
{
	while (buffer[len] == '9')
		len = ft_handling_nine(buffer, len);
	if (buffer[len] == '.')
		len--;
	if (buffer[len] >= '0' && buffer[len] < '9')
		buffer[len] = (buffer[len] - '0') + '1';
}

static void			ft_round_even(char *buffer, size_t len, \
				t_print *const clipb, unsigned int rounding_num)
{
	len--;
	if (buffer[len] == '.' && flagverif('.', clipb->flags) == -1)
		len--;
	if (buffer[len] == '9')
		ft_rounder_exception(buffer, len);
	else if (rounding_num == 5)
	{
		if (buffer[len] >= '3' && buffer[len] <= '9')
			buffer[len] = (buffer[len] - '0') + '1';
	}
	else
		buffer[len] = (buffer[len] - '0') + '1';
}

void				ft_float_rounder(char *buffer, \
				t_print *const restrict clipb, size_t nb_len)
{
	unsigned int		rounding_num;
	size_t				len;

	len = nb_len - 2;
	buffer = buffer + 1;
	while (buffer[len] == '.')
		len++;
	rounding_num = buffer[len] - '0';
	if (rounding_num >= 5)
	{
		if (buffer[len] == '9')
			ft_rounder_exception(buffer, len);
		else
			ft_round_even(buffer, len, clipb, rounding_num);
	}
}

void				ft_shrthd_rounder(char *buffer, \
				t_print *const restrict clipb, size_t nb_len)
{
	unsigned int		rounding_num;
	size_t				len;

	len = nb_len;
	buffer = buffer + 1;
	if (buffer[len] == '.')
		len++;
	rounding_num = buffer[len] - '0';
	if (rounding_num >= 5)
	{
		if (buffer[len] == '9')
			ft_rounder_exception(buffer, len);
		else
			ft_round_even(buffer, len, clipb, rounding_num);
	}
}
