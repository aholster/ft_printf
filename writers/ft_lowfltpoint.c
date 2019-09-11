/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowfltpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/09 13:45:41 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/11 13:03:24 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
// static int						rounder(size_t index, unsigned char *buf)
// {
// 	if (index > 0)
// 		index--;
// 	else
// 		return (1);
// 	while (buf[index] == '9' && index != 0)
// 	{
// 		buf[index] = '0';
// 		index--;
// 	}
// 	if (buf[index] != '9')
// 	{
// 		if (buf[index + 1] > 5)
// 		{
// 			buf[index]++;
// 			buf[index + 1] = '0';
// 		}
// 	}
// 	else
// 	{
// 		buf[index] = '0';
// 		return (1);
// 	}
// 	return (0);
// }

// static int					ft_printnum(int neg, t_print *clipb, \
// 						unsigned int nb_len)
// {
// 	if (neg != -1)
// 	{
// 		if (flagverif('+', clipb->flags) == 1)
// 			if (clipb->printer((const unsigned char*)"+", 1, clipb) == -1)
// 				return (-1);
// 		if (flagverif(' ', clipb->flags) == 1 && \
// 			flagverif('+', clipb->flags) == -1)
// 			if (clipb->printer((const unsigned char*)" ", 1, clipb) == -1)
// 				return (-1);
// 	}
// 	else if (clipb->printer((const unsigned char*)"-", 1, clipb) == -1)
// 		return (-1);
// 	if (flagverif('0', clipb->flags) == 1 && flagverif('-', clipb->flags) == -1)
// 		if (ft_zero_padder(nb_len, clipb) == -1)
// 			return (-1);
// 	return (1);
// }

// static int					ft_flt_padding(unsigned char *buffer, \
// 						int neg, unsigned short nb_len, t_print *clipb)
// {
// 	const unsigned char	*num;
// 	unsigned int		calc;

// 	num = (const unsigned char *)ft_itoa(nb_len - 1);
// 	calc = ft_strlen((const char *)num) + clipb->flags->precision;// + 2;
// 	if (flagverif('-', clipb->flags) == -1 && \
// 	flagverif('0', clipb->flags) == -1)
// 		if (ft_space_padder(calc, clipb) == -1)
// 			return (-1);
// 	if (ft_printnum(neg, clipb, calc) == -1)
// 		return (-1);
// 	if (clipb->printer(buffer, nb_len, clipb) == -1)
// 		return (-1);
// 	if (clipb->flags->precision != 0)
// 		if (clipb->printer((const unsigned char *)".", 1, clipb) == -1)
// 			return (-1);
// 	rounder((size_t)clipb->flags->precision - 1, &buffer[1]);
// 	ft_shorthand_prec(buffer, calc, clipb);
// 	if (clipb->printer(&buffer[nb_len], \
// 		clipb->flags->precision - nb_len, clipb) == -1)
// 		return (-1);
// 	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > calc)
// 		if (ft_space_padder(calc, clipb) == -1)
// 			return (-1);
// 	return (1);
// }

// static int					ft_lowshrthd_prec(unsigned char *buffer, int neg, \
// 						unsigned short nb_len, t_print *clipb)
// {
// 	const unsigned char	*num;
// 	unsigned int		calc;

// 	num = (const unsigned char *)ft_itoa(nb_len - 1);
// 	calc = clipb->flags->precision + ft_strlen((const char *)num); //+2
// 	if (flagverif('-', clipb->flags) == -1 && \
// 	flagverif('0', clipb->flags) == -1)
// 		if (ft_space_padder(calc, clipb) == -1)
// 			return (-1);
// 	rounder((size_t)clipb->flags->precision - 1, &buffer[1]);
// 	ft_shorthand_prec(buffer, nb_len, clipb);
// 	if (ft_printnum(neg, clipb, calc) == -1)
// 		return (-1);
// 	if (clipb->printer(buffer, nb_len, clipb) == -1)
// 		return (-1);
// 	if (clipb->flags->precision != 0)
// 		if (clipb->printer((const unsigned char *)".", 1, clipb) == -1)
// 			return (-1);
// 	if (clipb->printer(&buffer[nb_len], clipb->flags->precision, clipb) == -1)
// 		return (-1);
// 	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > calc)
// 		if (ft_space_padder(calc, clipb) == -1)
// 			return (-1);
// 	return (1);
// }


int						ft_lowfltpoint(va_list args, t_print *clipb)
{
	unsigned char		buffer[20];
	t_float				conversion;
	long double			nb;
	size_t				nb_len;
	int					neg;

	neg = ft_longdouble_conv(args, &nb, clipb->flags);
	conversion.ld = nb;
	nb_len = ft_ull_len(conversion.llu, 10);
	printf("nb_len: %zu\n", nb_len);
	printf("buffer: |%s|\n", buffer);
	if (ft_custom_ld_to_text(nb, clipb->flags->precision, (char**)&buffer, &nb_len) == -1)
		return (-1);
	printf("buffer: |%s|\n", buffer);
	// if (flagverif('.', clipb->flags) == -1)
	// 	return (ft_flt_padding(buffer, neg, nb_len, clipb));
	return (1);
}
