/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_float_handlers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/17 12:34:56 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/19 09:41:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

size_t				ft_x_offset(char **const buffer,\
						size_t *const nb_len,\
						const t_flag *const flags,\
						const int is_neg)
{
	size_t	offset;

	offset = 0;
	if (is_neg == 1)
	{
		if (flg_verif('+', flags) == 1)
			*buffer[0] = '+';
		else if (flg_verif(' ', flags) == 1)
			*buffer[0] = ' ';
		else if (flg_verif('+', flags) == -1 \
		&& flg_verif(' ', flags) == -1)
			offset++;
	}
	else if (is_neg == -1)
		*buffer[0] = '-';
	*buffer += offset;
	if (offset == 1)
		*nb_len -= 1;
	return (offset);
}

size_t				ft_float_exceptions(char *const buffer,\
						short *expon,\
						const t_flag *const flags)
{
	*expon = 0;
	buffer[0] = '0';
	if (flags->precision != 0)
	{
		buffer[1] = '.';
		buffer[2] = '0';
	}
	return (3);
}

unsigned short		ft_ull_len(unsigned long long num, const int base)
{
	unsigned short length;

	length = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= base;
		length++;
	}
	return (length);
}
