/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_padder.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 16:10:49 by aholster       #+#    #+#                */
/*   Updated: 2019/09/26 15:25:07 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"
#include <stdio.h>
int	pad_spaces(size_t amount, t_print *const clipb)
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
		if (clipb->printer(spaces, calc, clipb) == -1)
			return (-1);
		index += calc;
	}
	return (amount);
}

int	pad_zero(size_t amount, t_print *const clipb)
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
		if (clipb->printer(zeroes, calc, clipb) == -1)
			return (-1);
		index += calc;
	}
	return (amount);
}

int	ft_space_padder(unsigned short len, t_print *const clipb)
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
	else if (padding == precision && padding > len)
		diff = padding - len;
	else
		return (1);
	if (pad_spaces(diff, clipb) == -1)
		return (-1);
	return (1);
}

int	ft_zero_padder(unsigned short len, t_print *const clipb)
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

int	ft_float_padder(unsigned short len, unsigned short dec, t_print *const restrict clipb)
{
	if (clipb->flags->precision > len)
	{
		if (clipb->flags->precision > clipb->flags->padding)
		{
			if (pad_zero(clipb->flags->precision, clipb) == -1)
				return (-1);
		}
		else if (flagverif(' ', clipb->flags) == 1)
			if (pad_spaces(clipb->flags->precision, clipb) == -1)
				return (-1);
	}
	if (clipb->flags->padding > len)
	{
		if (clipb->flags->precision != dec)
			len += clipb->flags->precision;
		if (flagverif('0', clipb->flags) == 1)
		{
			if (pad_zero(clipb->flags->padding - len, clipb) == -1)
				return (-1);
		}
		else if (clipb->flags->padding > len)
			if (pad_spaces(clipb->flags->padding - len, clipb) == -1)
				return (-1);
	}
	return (1);
}
