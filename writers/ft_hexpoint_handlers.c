/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hexpoint_handlers.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/06 10:44:11 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/01 12:11:41 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

unsigned short		ft_hexpoint_prec(char *buffer, t_print *const clipb, \
				size_t nb_len, short expon)
{
	size_t			dec_len;
	unsigned short	len;

	len = nb_len;
	if (len == 1 && buffer[1] == '.')
		len++;
	if (expon == -1025)
		len = 0;
	if (flagverif('.', clipb->flags) == -1)
		len++;
	if (len > 2)
		dec_len = len - 2;
	else
		dec_len = 2;
	if (flagverif('.', clipb->flags) == 1)
	{
		if (dec_len > clipb->flags->precision && dec_len < len)
			len = (len - dec_len) + clipb->flags->precision;
		else if (dec_len < clipb->flags->precision && len > 2)
			clipb->flags->precision -= dec_len;
		if (clipb->flags->precision == 0 && len == 2)
			len--;
	}
	return (len);
}

int					ft_prefix(int neg, t_print *const clipb)
{
	if (neg >= 0)
	{
		if (flagverif('+', clipb->flags) == 1)
			if (clipb->printer("+", 1, clipb) == -1)
				return (-1);
		if (flagverif(' ', clipb->flags) == 1 && \
		flagverif('+', clipb->flags) == -1)
		{
			if (clipb->printer(" ", 1, clipb) == -1)
				return (-1);
		}
	}
	else if (neg < 0)
		if (clipb->printer("-", 1, clipb) == -1)
			return (-1);
	if (clipb->printer("0x", 2, clipb) == -1)
		return (-1);
	return (1);
}

unsigned short		ft_ull_len(unsigned long long num, int base)
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

unsigned short		ft_reversed(unsigned long long mantissa)
{
	unsigned short		len;
	unsigned long long	tempnum;

	tempnum = mantissa;
	len = 0;
	while (tempnum > 0)
	{
		tempnum >>= 4;
		len++;
	}
	return (len);
}

unsigned short		ft_negpos_handler(t_print *const restrict clipb, \
				int neg, short expon)
{
	unsigned short	sign;

	sign = 0;
	if (neg > 0)
	{
		if (flagverif('+', clipb->flags) == 1 || \
		flagverif(' ', clipb->flags) == 1)
			sign++;
	}
	else if (neg < 0)
		sign++;
	if (expon >= 0)
		sign++;
	return (sign);
}
