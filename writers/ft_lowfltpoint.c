/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowfltpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/09 13:45:41 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/16 19:04:50 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

// static int					ft_printnum(int neg, t_print *const clipb, \
// 						unsigned int nb_len)
// {
// 	if (neg != -1)
// 	{
// 		if (flagverif('+', clipb->flags) == 1)
// 			if (clipb->printer("+", 1, clipb) == -1)
// 				return (-1);
// 		if (flagverif(' ', clipb->flags) == 1 && \
// 			flagverif('+', clipb->flags) == -1)
// 			if (clipb->printer(" ", 1, clipb) == -1)
// 				return (-1);
// 	}
// 	else if (clipb->printer("-", 1, clipb) == -1)
// 		return (-1);
// 	if (flagverif('0', clipb->flags) == 1 && flagverif('-', clipb->flags) == -1)
// 		if (ft_zero_padder(nb_len, clipb) == -1)
// 			return (-1);
// 	return (1);
// }

// static int					ft_flt_padding(unsigned char *buffer, \
// 						int neg, unsigned short nb_len, t_print *const clipb)
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
// 						unsigned short nb_len, t_print *const clipb)
// {
// 	const unsigned char	*num;
// 	unsigned int		calc;

static void	ft_x_handler(char *buffer)
{
	size_t index;

	index = 0;
	while (buffer[index] != '\0')
	{
		buffer[index] = buffer[index + 1];
		index++;
	}
}

static int	ft_float_padding(char *buffer, \
			int neg, t_print *const clipb, size_t nb_len)
{
	nb_len--;
	if (flagverif('+', clipb->flags) == -1)
		nb_len--;
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (ft_prefix(neg, clipb) == -1)
		return (-1);
	ft_x_handler(buffer);
	if (flagverif('+', clipb->flags) == 1)
		nb_len--;
	if (flagverif('0', clipb->flags) == 1 && flagverif('-', clipb->flags) == -1)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, nb_len, clipb) == -1)
		return (-1);
	if (neg == -1)
		nb_len++;
	if (flagverif('-', clipb->flags) == 1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

int			ft_lowfltpoint(va_list args, t_print *const clipb)
{
	char				*buffer;
	t_float				conversion;
	long double			nb;
	size_t				nb_len;
	int					neg;

	neg = ft_longdouble_conv(args, &nb, clipb->flags);
	conversion.ld = nb;
	nb_len = (size_t)ft_ull_len(conversion.llu, 10);
	if (flagverif('.', clipb->flags) == -1)
		clipb->flags->precision = 6;
	if (ft_custom_ld_to_text(nb, \
	clipb->flags->precision, &buffer, &nb_len) == -1)
		return (-1);
	ft_rounder(conversion, buffer, clipb, nb_len);
	return (ft_float_padding(buffer, neg, clipb, nb_len));
}
