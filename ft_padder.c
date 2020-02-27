/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_padder.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/25 16:10:49 by aholster       #+#    #+#                */
/*   Updated: 2020/02/27 15:35:44 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/ft_internals.h"

void	pad_spaces(size_t amount, t_writer *const clipb)
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
		ft_write_wrap(spaces, calc, clipb);
		amount -= calc;
	}
}

void	pad_zero(size_t amount, t_writer *const clipb)
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
		ft_write_wrap(zeroes, calc, clipb);
		amount -= calc;
	}
}

void	ft_space_padder(const unsigned short len, t_writer *const clipb)
{
	const unsigned int	padding = clipb->flags->padding;
	const unsigned int	precision = clipb->flags->precision;
	const size_t		temp = padding - precision;
	size_t				diff;

	if (padding < 1 && precision < 1)
		return ;
	if (padding > precision && precision > len)
		diff = temp;
	else if (padding > precision && padding > len)
		diff = padding - len;
	else if (padding == precision && padding > len)
		diff = padding - len;
	else
		return ;
	pad_spaces(diff, clipb);
}

void	ft_zero_padder(const unsigned short len, t_writer *const clipb)
{
	const unsigned int	padding = clipb->flags->padding;
	const unsigned int	precision = clipb->flags->precision;
	const size_t		temp = padding - precision;
	size_t				diff;

	if (padding < 1 && precision < 1)
		return ;
	else if (temp > len && flg_verif('.', clipb->flags) == -1)
		diff = temp - len;
	else if (precision > len && flg_verif('.', clipb->flags) == 1)
		diff = precision - len;
	else if (padding > precision && precision > len)
		diff = temp;
	else if (padding > precision && padding > len)
		diff = padding - len;
	else
		return ;
	pad_zero(diff, clipb);
}

void	ft_float_padder(unsigned short len,\
			const unsigned short dec,\
			t_writer *const clipb)
{
	if (clipb->flags->precision > len)
	{
		if (clipb->flags->precision > clipb->flags->padding)
		{
			pad_zero(clipb->flags->precision, clipb);
		}
		else if (flg_verif(' ', clipb->flags) == 1)
		{
			pad_spaces(clipb->flags->precision, clipb);
		}
	}
	if (clipb->flags->padding > len)
	{
		if (clipb->flags->precision != dec)
			len += clipb->flags->precision;
		if (flg_verif('0', clipb->flags) == 1)
		{
			pad_zero(clipb->flags->padding - len, clipb);
		}
		else if (clipb->flags->padding > len)
		{
			pad_spaces(clipb->flags->padding - len, clipb);
		}
	}
}
