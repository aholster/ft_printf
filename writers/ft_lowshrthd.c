/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowshrthd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/21 12:57:35 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/16 16:00:03 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>
static int						rounder(size_t index, char *buf)
{
	if (index > 0)
		index--;
	else
		return (1);
	while (buf[index] == '9' && index != 0)
	{
		buf[index] = '0';
		index--;
	}
	if (buf[index] != '9')
	{
		if (buf[index + 1] > 5)
		{
			buf[index]++;
			buf[index + 1] = '0';
		}
	}
	else
	{
		buf[index] = '0';
		return (1);
	}
	return (0);
}

static int					ft_printnum(int neg, t_print *clipb, \
						unsigned int nb_len)
{
	if (neg != -1)
	{
		if (flagverif('+', clipb->flags) == 1)
			if (clipb->printer("+", 1, clipb) == -1)
				return (-1);
		if (flagverif(' ', clipb->flags) == 1 && \
			flagverif('+', clipb->flags) == -1)
			if (clipb->printer(" ", 1, clipb) == -1)
				return (-1);
	}
	else if (clipb->printer("-", 1, clipb) == -1)
		return (-1);
	if (flagverif('0', clipb->flags) == 1 && flagverif('-', clipb->flags) == -1)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static int					ft_lowshrthd_noprec(char *buffer, \
						int neg, unsigned short nb_len, t_print *clipb)
{
	const char	*num;
	unsigned int		calc;

	num = ft_itoa(nb_len - 1);
	calc = ft_strlen(num) + clipb->flags->precision;// + 2;
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(calc, clipb) == -1)
			return (-1);
	if (ft_printnum(neg, clipb, calc) == -1)
		return (-1);
	if (clipb->printer(buffer, nb_len, clipb) == -1)
		return (-1);
	if (clipb->flags->precision != 0)
		if (clipb->printer(".", 1, clipb) == -1)
			return (-1);
	rounder((size_t)clipb->flags->precision - 1, &buffer[1]);
	ft_shorthand_prec(buffer, calc, clipb);
	if (clipb->printer(&buffer[nb_len], \
		clipb->flags->precision - nb_len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > calc)
		if (ft_space_padder(calc, clipb) == -1)
			return (-1);
	return (1);
}

// static int					ft_lowshrthd_prec(char *buffer, int neg, \
// 						unsigned short nb_len, t_print *clipb)
// {
// 	const char	*num;
// 	unsigned int		calc;

// 	num = ft_itoa(nb_len - 1);
// 	calc = clipb->flags->precision + ft_strlen(num); //+2
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
// 		if (clipb->printer(".", 1, clipb) == -1)
// 			return (-1);
// 	if (clipb->printer(&buffer[nb_len], clipb->flags->precision, clipb) == -1)
// 		return (-1);
// 	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > calc)
// 		if (ft_space_padder(calc, clipb) == -1)
// 			return (-1);
// 	return (1);
// }

// static unsigned long long	ft_float_buffer(long double num, \
// 						char *buffer, t_print *clipb)
// {
// 	unsigned char		subnum;
// 	size_t				index;
// 	unsigned long long	longcast;

// 	index = ft_strlen(buffer);
// 	longcast = (unsigned long long)num;
// 	num -= longcast;
// 	while (clipb->flags->precision >= index)
// 	{
// 		num *= 10;
// 		subnum = (unsigned char)num;
// 		buffer[index] = subnum + '0';
// 		num -= subnum;
// 		index++;
// 	}
// 	num *= 10;
// 	if (num > 5)
// 		return (longcast += rounder(index, buffer));
// 	else if (num == 5)
// 	{
// 		if ((longcast & 1) == 1)
// 			return (longcast + 1);
// 	}
// 	return (longcast);
// }

// static unsigned short		ft_int_len(char *buffer, \
// 						long double nb, t_print *clipb)
// {
// 	unsigned long long	temp_num;
// 	unsigned short		prec_len;
// 	unsigned short		cur_len;
// 	char				*base;

// 	base = "0123456789";
// 	temp_num = nb;
// 	prec_len = ft_ull_len(nb, 10);
// 	cur_len = prec_len - 1;
// 	if (nb == 0)
// 	{
// 		ft_strcpy((char *)buffer, "0000000");
// 		return (1);
// 	}
// 	while (temp_num >= 10)
// 	{
// 		buffer[cur_len] = base[(temp_num % 10)];
// 		temp_num /= 10;
// 		cur_len--;
// 	}
// 	buffer[cur_len] = base[temp_num];
// 	ft_float_buffer(nb, buffer, clipb);
// 	return (prec_len);
// }

int							ft_lowshrthd(va_list args, t_print *clipb)
{
 	char				*buffer;
	t_float				conversion;
	long double			nb;
	size_t				nb_len;
	int					neg;

	neg = ft_longdouble_conv(args, &nb, clipb->flags);
	conversion.ld = nb;
	if (flagverif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	// else if (clipb->flags->precision == 0)
	// 	clipb->flags->precision = 1;
	//nb_len = ft_int_len(buffer, nb, clipb);
	nb_len = ft_ull_len(conversion.llu, 10);
	if (ft_custom_ld_to_text(nb, \
	clipb->flags->precision, &buffer, &nb_len) == -1)
		return (-1);
	printf("buffer: |%s|\n", buffer);
	if (clipb->flags->padding != 0 && (neg == -1 || \
	flagverif('+', clipb->flags) == 1 || flagverif(' ', clipb->flags) == 1))
		clipb->flags->padding -= 1;
	// if (flagverif('.', clipb->flags) == 1)
	// 	return (ft_lowshrthd_prec(buffer, neg, nb_len, clipb));
	if (flagverif('.', clipb->flags) == -1)
		return (ft_lowshrthd_noprec(buffer, neg, nb_len, clipb));
	return (1);
}
