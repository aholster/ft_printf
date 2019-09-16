/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_capsci.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/21 11:16:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/16 19:04:50 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

static int				ft_printnum(int neg, t_print *const clipb, \
							char *buffer, unsigned int nb_len)
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
	if (clipb->printer(buffer, 1, clipb) == -1)
		return (-1);
	if (clipb->flags->precision != 0)
		if (clipb->printer(".", 1, clipb) == -1)
			return (-1);
	if (clipb->printer(&buffer[1], clipb->flags->precision, clipb) == -1)
		return (-1);
	return (1);
}

static int				ft_capsci_neg(char *buffer, int neg, \
					unsigned short nb_len, t_print *const clipb)
{
	const char			*num;
	unsigned int		calc;

	num = ft_itoa(nb_len - 1);
	calc = clipb->flags->precision + 4 + ft_strlen(num);
	if (nb_len - 1 < 10)
		calc++;
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(calc, clipb) == -1)
			return (-1);
	if (ft_printnum(neg, clipb, buffer, calc) == -1)
		return (-1);
	if (clipb->printer("E-", 2, clipb) == -1)
		return (-1);
	if (nb_len - 1 < 10)
		if (clipb->printer("0", 1, clipb) == -1)
			return (-1);
	if (clipb->printer(num, \
	ft_strlen(num), clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > calc)
		if (ft_space_padder(calc, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_capsci_pos(char *buffer, int neg, \
					unsigned short nb_len, t_print *const clipb)
{
	const char			*num;
	unsigned int		calc;

	num = ft_itoa(nb_len - 1);
	calc = clipb->flags->precision + 4 + ft_strlen(num);
	if (nb_len - 1 < 10)
		calc++;
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(calc, clipb) == -1)
			return (-1);
	if (ft_printnum(neg, clipb, buffer, calc) == -1)
		return (-1);
	if (clipb->printer("E+", 2, clipb) == -1)
		return (-1);
	if (nb_len - 1 < 10)
		if (clipb->printer("0", 1, clipb) == -1)
			return (-1);
	if (clipb->printer(num, \
	ft_strlen(num), clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > calc)
		if (ft_space_padder(calc, clipb) == -1)
			return (-1);
	return (1);
}

static int	rounder(size_t index, char *buf)
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
		buf[index]++;
	else
	{
		buf[index] = '0';
		return (1);
	}
	return (0);
}

static unsigned long long	ft_float_buffer(long double num, char *buffer, t_print *const clipb)
{
	unsigned char subnum;
	size_t	index;
	unsigned long long longcast;

	index = ft_strlen(buffer);
	longcast = (unsigned long long)num;
	num -= longcast;
	while (clipb->flags->precision >= index)
	{
		num *= 10;
		subnum = (unsigned char)num;
		buffer[index] = subnum + '0';
		num -= subnum;
		index++;
	}
	num *= 10;
	if (num > 5)
		return (longcast += rounder(index, buffer));
	else if (num == 5)
	{
		if ((longcast & 1) == 1)
			return (longcast + 1);
		else
			return (longcast);
	}
	return (longcast);
}

static unsigned short	ft_int_len(char *buffer, \
					long double nb, t_print *const clipb)
{
	unsigned long long	temp_num;
	unsigned short		prec_len;
	unsigned short		cur_len;
	char				*base;

	base = "0123456789";
	temp_num = nb;
	prec_len = ft_ull_len(nb, 10);
	cur_len = prec_len - 1;
	if (nb == 0)
	{
		ft_strcpy((char *)buffer, "0000000");
		return (1);
	}
	while (temp_num >= 10)
	{
		buffer[cur_len] = base[(temp_num % 10)];
		temp_num /= 10;
		cur_len--;
	}
	buffer[cur_len] = base[temp_num];
	ft_float_buffer(nb, buffer, clipb);
	return (prec_len);
}

static int				ft_isinfnan(float f, t_print *const clipb)
{
	long l;

	l = *((long *)&f);
	if (f != f)
	{
		if (clipb->printer("NAN", 3, clipb) == -1)
			return (-1);
		return (1);
	}
	if (l == 0x7F800000)
	{
		if (clipb->printer("INF", 3, clipb) == -1)
			return (-1);
		return (1);
	}
	if (l == 0xFF800000)
	{
		if (clipb->printer("-INF", 4, clipb) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int						ft_capsci(va_list args, t_print *const clipb)
{
	char				buffer[200000];
	long double			nb;
	unsigned long long	nb_len;
	int					neg;

	neg = 1;
	if (ft_longdouble_conv(args, &nb, clipb->flags) == -1)
		neg = -1;
	if (ft_isinfnan((float)nb, clipb) == -1)
		return (-1);
	if (flagverif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	nb_len = ft_int_len(buffer, nb, clipb);
	if (clipb->flags->padding != 0 && (neg == -1 || \
	flagverif('+', clipb->flags) == 1 || flagverif(' ', clipb->flags) == 1))
		clipb->flags->padding -= 1;
	if (nb >= 0)
		return (ft_capsci_pos(buffer, neg, nb_len, clipb));
	if (nb < 0)
		return (ft_capsci_neg(buffer, neg, nb_len, clipb));
	return (1);
}
