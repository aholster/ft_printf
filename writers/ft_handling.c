/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handling.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/06 10:44:11 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/30 12:20:20 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

unsigned short		ft_lowhexpoint_prec(char *buffer, t_print *const clipb)
{
	size_t			dec_len;
	unsigned short	len;

	len = (unsigned short)ft_strlen((const char*)buffer) - 1;
	if (len == 1 && buffer[1] == '.')
		len++;
	if (flagverif('.', clipb->flags) == -1)
		len++;
	if (len > 2)
		dec_len = len - 2;
	else
		dec_len = 2;
	if (flagverif('.', clipb->flags) == 1)
	{
		if (clipb->flags->precision == 0 && len == 1)
			len++;
		if (dec_len > clipb->flags->precision && dec_len < len)
			len = (len - dec_len) + clipb->flags->precision;
		else if (dec_len < clipb->flags->precision && len > 2)
			clipb->flags->precision -= dec_len;
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
	else if (neg < 0 || flagverif('-', clipb->flags) == 1)
		if (clipb->printer("-", 1, clipb) == -1)
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

unsigned short		ft_negpos_handler(t_print *const restrict clipb, \
				int neg)
{
	unsigned short	sign;

	sign = 0;
	if (neg == 1)
	{
		if (flagverif('+', clipb->flags) == 1 || \
		flagverif(' ', clipb->flags) == 1)
			sign++;
	}
	else if (neg == -1)
		sign++;
	return (sign);
}
