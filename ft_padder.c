/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_padder.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 16:10:49 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 10:44:01 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/ft_internals.h"

int	pad_spaces(size_t amount, t_writer *const clipb)
{
	uint16_t	calc;
	const char	spaces[] = {
	"                                                                "};

	while (amount != 0)
	{
		if (amount < 64)
			calc = amount;
		else
			calc = 64;
		if (clipb->self(spaces, calc, clipb) == -1)
			return (-1);
		amount -= calc;
	}
	return (1);
}

int	pad_zero(size_t amount, t_writer *const clipb)
{
	uint16_t	calc;
	const char	zeroes[] = {
	"0000000000000000000000000000000000000000000000000000000000000000"};

	while (amount != 0)
	{
		if (amount < 64)
			calc = amount;
		else
			calc = 64;
		if (clipb->self(zeroes, calc, clipb) == -1)
			return (-1);
		amount -= calc;
	}
	return (1);
}

int	ft_space_padder(const unsigned short len, t_writer *const clipb)
{
	const unsigned int	padding = clipb->flags->padding;
	const unsigned int	precision = clipb->flags->precision;
	const size_t		temp = padding - precision;
	size_t				diff;

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

int	ft_zero_padder(const unsigned short len, t_writer *const clipb)
{
	const unsigned int	padding = clipb->flags->padding;
	const unsigned int	precision = clipb->flags->precision;
	const size_t		temp = padding - precision;
	size_t				diff;

	if (padding < 1 && precision < 1)
		return (1);
	else if (temp > len && flg_verif('.', clipb->flags) == -1)
		diff = temp - len;
	else if (precision > len && flg_verif('.', clipb->flags) == 1)
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

int	ft_float_padder(unsigned short len,\
		const unsigned short dec,\
		t_writer *const clipb)
{
	if (clipb->flags->precision > len)
	{
		if (clipb->flags->precision > clipb->flags->padding)
		{
			if (pad_zero(clipb->flags->precision, clipb) == -1)
				return (-1);
		}
		else if (flg_verif(' ', clipb->flags) == 1)
			if (pad_spaces(clipb->flags->precision, clipb) == -1)
				return (-1);
	}
	if (clipb->flags->padding > len)
	{
		if (clipb->flags->precision != dec)
			len += clipb->flags->precision;
		if (flg_verif('0', clipb->flags) == 1)
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
