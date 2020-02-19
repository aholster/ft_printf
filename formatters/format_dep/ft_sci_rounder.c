/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sci_rounder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 17:42:52 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/19 09:41:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

static size_t		ft_handle_nine(char *buffer, size_t len, size_t *nb_len)
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
		nb_len++;
	}
	if (buffer[len] == '.')
		len--;
	return (len);
}

static void			ft_sci_exception(char *buffer, size_t len, size_t *nb_len)
{
	while (buffer[len] == '9')
	{
		len = ft_handle_nine(buffer, len, nb_len);
	}
	if (buffer[len] == '.' && len > 1)
	{
		len--;
		buffer[len] = (buffer[len] - '0') + '1';
	}
	else if (buffer[len] >= '0' && buffer[len] < '9' && len > 1)
		buffer[len] = (buffer[len] - '0') + '1';
}

static void			ft_add_one(char *buffer, size_t len)
{
	if (buffer[len] == '.')
		len--;
	if (buffer[len] != '2')
		buffer[len] = (buffer[len] - '0') + '1';
}

void				ft_sci_rounder(char *buffer,\
						const t_flag *const flags,\
						size_t *nb_len)
{
	unsigned int		precision;
	unsigned int		rounding_num;
	size_t				len;
	size_t				roundex;

	len = 0;
	roundex = *nb_len - 1;
	precision = flags->precision;
	if (buffer[roundex] == '.')
		roundex++;
	rounding_num = buffer[roundex] - '0';
	while (buffer[len] != '.')
		len++;
	len += precision + 1;
	if (rounding_num >= 5 && rounding_num < 10)
	{
		len--;
		if (buffer[len] == '9')
			ft_sci_exception(buffer, len, nb_len);
		else if ((buffer[len] >= '0' && buffer[len] < '9')\
			|| buffer[len] == '.')
			ft_add_one(buffer, len);
	}
}

size_t				ft_expon_rounding(char *buffer,\
						size_t nb_len,\
						const t_flag *const flags,
						short expon)
{
	size_t			index;
	size_t			rounded;
	unsigned int	precision;

	index = 0;
	rounded = 0;
	if (expon == 308)
		return (495);
	precision = flags->precision;
	while (buffer[index] != '.' && index < nb_len)
		index++;
	if (buffer[index] == '.')
	{
		if (buffer[index + 1] == '9' && buffer[index - 1] == '9')
			rounded++;
	}
	return (rounded);
}
