/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_float_rounder.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 10:14:39 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/19 09:41:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

static size_t		ft_handling_nine(char *buffer, size_t len, size_t *nb_len)
{
	if (buffer[len] == '9' && buffer[len - 1] != '.' && len > 1)
		buffer[len] = '0';
	else if (buffer[len] != '9' && buffer[len - 1] != '.')
		buffer[len] = (buffer[len] - '0') + '1';
	else if (buffer[len] == '9' && buffer[len - 1] == '.')
	{
		if (len == 2 && buffer[len - 2] == '9')
		{
			buffer[len] = '.';
			len--;
			*nb_len += 1;
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

static void			ft_rounder_exception(char *buffer,\
						size_t len,\
						size_t *nb_len)
{
	while (buffer[len] == '9')
		len = ft_handling_nine(buffer, len, nb_len);
	if (buffer[len] == '.')
		len--;
	if (buffer[len] >= '0' && buffer[len] < '9')
		buffer[len] = (buffer[len] - '0') + '1';
}

static void			ft_round_even(char *buffer,\
						size_t len,\
						const t_flag *const flags,\
						unsigned int rounding_num)
{
	size_t len_hold;

	len_hold = len;
	len--;
	if (buffer[len] == '.' && flg_verif('.', flags) == -1)
		len--;
	if (buffer[len] == '9')
		ft_rounder_exception(buffer, len, &len_hold);
	else if (rounding_num == 5)
	{
		if (buffer[len] >= '3' && buffer[len] <= '9')
			buffer[len] = (buffer[len] - '0') + '1';
	}
	else
		buffer[len] = (buffer[len] - '0') + '1';
}

void				ft_float_rounder(char *buffer,\
						const t_flag *const flags,\
						size_t *nb_len)
{
	unsigned int		rounding_num;
	size_t				len;

	len = *nb_len - 2;
	buffer = buffer + 1;
	while (buffer[len] == '.')
		len++;
	rounding_num = buffer[len] - '0';
	if (rounding_num >= 5)
	{
		if (buffer[len] == '9')
			ft_rounder_exception(buffer, len, nb_len);
		else
			ft_round_even(buffer, len, flags, rounding_num);
	}
}

void				ft_shrthd_rounder(char *buffer,\
						const t_flag *const flags,\
						size_t *nb_len)
{
	unsigned int		rounding_num;
	size_t				len;

	len = *nb_len;
	buffer = buffer + 1;
	if (buffer[len] == '.')
		len++;
	rounding_num = buffer[len] - '0';
	if (rounding_num >= 5)
	{
		if (buffer[len] == '9')
			ft_rounder_exception(buffer, len, nb_len);
		else
			ft_round_even(buffer, len, flags, rounding_num);
	}
}
