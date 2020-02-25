/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hexpoint_rounder.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/19 16:00:34 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/19 10:41:31 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

static void		ft_add_one(char *buffer, size_t index)
{
	if (buffer[index] == '.')
		index--;
	buffer[index] = (buffer[index] - '0') + '1';
}

static size_t	ft_rounding_handler(char *buffer,\
					size_t index,\
					const char *const base_ref)
{
	char			holder;
	size_t			judex;

	holder = '\0';
	judex = 0;
	if ((buffer[index] - '0') > 8 \
	&& (buffer[index] - '0') < (base_ref[15] - '0'))
	{
		holder = (buffer[index] - '0');
		while (base_ref[judex] != holder && base_ref != '\0')
			judex++;
		judex++;
		buffer[index] = (base_ref[judex] - '0');
	}
	else if ((buffer[index] - '0') == (base_ref[15] - '0'))
	{
		buffer[index] = '0';
		index--;
	}
	return (index);
}

static void		ft_dlbmax_case(char *buffer, \
					short *expon,\
					const t_flag *const flags)
{
	size_t index;

	index = 2;
	*expon = 1024;
	buffer[0] = '1';
	buffer[1] = '.';
	while (index < flags->precision + 2)
	{
		buffer[index] = '0';
		index++;
	}
}

static void		ft_rounding_up(char *buffer,\
					size_t index,\
					const char *const base_ref)
{
	char	holder;
	size_t	judex;

	holder = '\0';
	judex = 0;
	while ((buffer[index] - '0') > 8 \
	&& (buffer[index] - '0') <= (base_ref[15] - '0'))
		index = ft_rounding_handler(buffer, index, base_ref);
	if (buffer[index] == '.')
	{
		index--;
		if ((buffer[index] - '0') < (base_ref[9] - '0'))
			buffer[index] = (buffer[index] - '0') + '1';
		else
		{
			holder = buffer[index];
			while (base_ref[judex] != holder)
				judex++;
			judex++;
			buffer[index] = base_ref[judex];
		}
		if ((buffer[index] - '0') >= 0 && (buffer[index] - '0') < 9)
			ft_add_one(buffer, index);
	}
}

void			ft_hexpoint_rounder(char *buffer,\
					const t_flag *const flags,\
					short *expon)
{
	unsigned int	precision;
	size_t			index;
	size_t			judex;
	const char		base_ref[] = "0123456789abcdef";

	judex = 0;
	precision = flags->precision + 2;
	index = flags->precision + 2;
	if ((buffer[precision] - '0') > (base_ref[5] - '0'))
	{
		index--;
		if ((buffer[index] - '0') > 8 \
		&& (buffer[index] - '0') <= (base_ref[15] - '0'))
		{
			if (*expon == 1020 && flg_verif('.', flags) == 1)
				ft_dlbmax_case(buffer, expon, flags);
			else if (*expon != 1020)
				ft_rounding_up(buffer, index, base_ref);
		}
		else if ((buffer[index] - '0') >= 0 && (buffer[index] - '0') < 9)
			ft_add_one(buffer, index);
	}
}
