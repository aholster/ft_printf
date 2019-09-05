/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_padder.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 16:10:49 by aholster       #+#    #+#                */
/*   Updated: 2019/09/05 16:49:26 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_shortprec(unsigned char *buffer, unsigned short nb_len, \
	t_print *clipb)
{
	size_t index;
	size_t holder;

	index = nb_len;
	holder = 0;
	while (index < clipb->flags->precision)
	{
		while (buffer[index] != '0' && index < clipb->flags->precision + 1)
			index++;
		if (buffer[index] == '0' && index < clipb->flags->precision + 1)
		{
			holder = index - 1;
			while (buffer[index] == '0' && index < clipb->flags->precision + 1)
				index++;
		}
	}
	if (index > holder && holder != 0)
		clipb->flags->precision = index - holder;
}

int	pad_spaces(size_t amount, t_print *clipb)
{
	size_t		index;
	size_t		calc;
	const char	*spaces = "                                                                ";

	index = 0;
	while (index < amount)
	{
		if (amount - index < sizeof(spaces))
			calc = amount - index;
		else
			calc = sizeof(spaces);
		if (clipb->printer((const unsigned char *)spaces, calc, clipb) == -1)
			return (-1);
		index += calc;
	}
	return (amount);
}

int	pad_zero(size_t amount, t_print *clipb)
{
	size_t		index;
	size_t		calc;
	const char	*zeroes = "0000000000000000000000000000000000000000000000000000000000000000";

	index = 0;
	while (index < amount)
	{
		if (amount - index < sizeof(zeroes))
			calc = amount - index;
		else
			calc = sizeof(zeroes);
		if (clipb->printer((const unsigned char *)zeroes, calc, clipb) == -1)
			return (-1);
		index += calc;
	}
	return (amount);
}

int	ft_space_padder(unsigned short len, t_print *clipb)
{
	size_t			diff;
	size_t			temp;
	unsigned int	padding;
	unsigned int	precision;

	padding = clipb->flags->padding;
	precision = clipb->flags->precision;
	temp = padding - precision;
	if (padding < 1 && precision < 1)
		return (1);
	if (padding > precision && precision > len)
		diff = temp;
	else if (padding > precision && padding > len)
		diff = padding - len;
	else
		return (1);
	if (pad_spaces(diff, clipb) == -1)
		return (-1);
	return (1);
}

int	ft_zero_padder(unsigned short len, t_print *clipb)
{
	size_t			diff;
	size_t			temp;
	unsigned int	padding;
	unsigned int	precision;

	padding = clipb->flags->padding;
	precision = clipb->flags->precision;
	temp = padding - precision;
	if (padding < 1 && precision < 1)
		return (1);
	else if (temp > len && flagverif('.', clipb->flags) == -1)
		diff = temp - len;
	else if (precision > len && flagverif('.', clipb->flags) == 1)
		diff = precision - len;
	else if (padding > precision && precision > len)
		diff = temp;
	else if (padding > precision && padding > len)
		diff = padding - len;
	else
		return (1);
	if (pad_zero(diff, clipb) == -1)
		return (-1);
	return (1);
}
