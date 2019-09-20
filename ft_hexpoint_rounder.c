/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hexpoint_rounder.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/19 16:00:34 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/20 13:11:35 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static void	ft_add_one(char *buffer, size_t index)
{
			index--;
			if (buffer[index] == '.')
				index--;
			buffer[index] = (buffer[index] - '0') + '1';
}

static size_t	ft_rounding_handler(char *buffer, size_t index, char *base_ref)
{
	char			holder;
	size_t			judex;

	index--;
	holder = '\0';
	judex = 0;
	if ((buffer[index] - '0') >= (base_ref[0] - '0') \
	&& (buffer[index] - '0') < (base_ref[8] - '0'))
		buffer[index] = (buffer[index] - '0') + '1';
	else if ((buffer[index] - '0') > (base_ref[8] - '0') \
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
		buffer[index] = (base_ref[0] - '0');
		index--;
	}
	return (index);
}

static void		ft_dlbmax_case(char *buffer, \
			short *expon, t_print *const restrict clipb)
{
	size_t index;

	index = 2;
	*expon = 1024;
	buffer[0] = '1';
	buffer[1] = '.';
	while (index < clipb->flags->precision + 2)
	{
		buffer[index] = '0';
		index++;
	}
}

static void		ft_rounding_up(char *buffer, size_t index, \
			char* base_ref)
{
	char	holder;
	size_t	judex;

	holder = '\0';
	judex = 0;
	while ((buffer[index] - '0') > (base_ref[8] - '0') \
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
	}
}

void		ft_hexpoint_rounder(char *buffer, \
		t_print *const restrict clipb, short *expon)
{
	unsigned int	precision;
	char			*base_ref;
	size_t			index;
	size_t			judex;

	judex = 0;
	base_ref = "0123456789abcdef";
	precision = clipb->flags->precision + 2;
	index = clipb->flags->precision + 2;
	if ((buffer[precision] - '0') > (base_ref[5] - '0'))
	{
		if ((buffer[index] - '0') > (base_ref[8] - '0') \
		&& (buffer[index] - '0') <= (base_ref[15] - '0'))
		{
			if (*expon == 1020 && flagverif('.', clipb->flags) == 1)
				ft_dlbmax_case(buffer, expon, clipb);
			else if (*expon != 1020)
			ft_rounding_up(buffer, index, base_ref);
			else if ((buffer[index] - '0') <= (base_ref[0] - '0') \
			&& (buffer[index] - '0') < (base_ref[9] - '0'))
				ft_add_one(buffer, index);
		}
	}
}
