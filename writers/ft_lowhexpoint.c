/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowhexpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/28 14:42:40 by jesmith        #+#    #+#                */
/*   Updated: 2019/08/29 18:47:16 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int				ft_signhand(int neg, t_print *clipb)
{
	if (neg != -1)
	{
		if (flagverif('+', clipb->flags) == 1)
			if (clipb->printer((const unsigned char*)"+", 1, clipb) == -1)
				return (-1);
		if (flagverif(' ', clipb->flags) == 1 && \
		flagverif('+', clipb->flags) == -1)
		{
			if (clipb->printer((const unsigned char*)" ", 1, clipb) == -1)
				return (-1);
		}
	}
	else if (clipb->printer((const unsigned char*)"-", 1, clipb) == -1)
		return (-1);
	return (1);
}

// static int				exponentbuffer(t_print *clipb, int neg)
// {
// 	unsigned char	buffer[8];
// 	unsigned short	exponent;
// 	size_t			index;

// 	exponent = (conversion.shrt[4] & 0x7FFF) - 16383;
// 	index = 1;
// 	buffer[0] = 'p';
// 	if (neg == -1)
// 		buffer[index] = '-';
// 	else
// 		buffer[index] = '+';
// 	index++;
// 	while (exponent > 10)
// 	{
// 		buffer[index] = ((exponent % 10) + '0');
// 		exponent /= 10;
// 		index++;
// 	}
// 	buffer[index] = exponent;
// 	if (clipb->printer(buffer, (int)index, clipb) == -1)
// 		return (-1);
// 	return (1);
// }

static int				ft_lowshrthd_prec(unsigned char *buffer, int neg, \
					unsigned short nb_len, t_print *clipb)
{
	if (flagverif('-', clipb->flags) == -1 && flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (ft_signhand(neg, clipb) == -1)
		return (-1);
	if (clipb->printer((const unsigned char *)"0x1.", 4, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == -1 && flagverif('0', clipb->flags) == 1)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, nb_len, clipb) == -1)
		return (-1);
	if (clipb->flags->precision > nb_len && flagverif('.', clipb->flags) == 1)
		if (ft_zero_padder(clipb->flags->precision - nb_len, clipb) == -1)
			return (-1);
	// if (exponentbuffer(clipb, neg) == -1)
	// 	return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > nb_len) // this is for no prec see if works here 
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (flagverif('-', clipb->flags) == -1 && flagverif('0', clipb->flags) == 1)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static unsigned short				ft_man_to_buffer(t_float conversion, unsigned char *buffer)
{
	char				*base;
	unsigned long long	temp;
	unsigned short		nb_len;
	unsigned short		cur_len;

	base = "0123456789abcdef";
	nb_len = (unsigned short)ft_nbrlen(conversion.llu, 16);
	cur_len = nb_len - 1;
	temp = conversion.llu;
	// if (mantissa == 0)
	// {
	// 	buffer[0] = '0';
	// 	return (2);
	// }
	printf("1conversion.llu %llu\n", temp);
	conversion.shrt[cur_len] = (temp % 16) + '0';
	while (temp >= 16)
	{
		buffer[cur_len] = base[(temp % 16)];
		temp /= 16;
		cur_len--;
	}
	buffer[cur_len] = base[temp];
	printf("buffer: %s\n", buffer);
	printf("short : %hu\n", conversion.shrt[0]);
	return (nb_len);
}

static unsigned long long			ft_extraction(long double nb)
{
	t_float				extract;
	unsigned char		counter;
	unsigned long long	reverse;
	unsigned long long	temp;
	//unsigned short		expon;

	extract.ld = nb;
	temp = extract.llu;
	//expon = (conversion.shrt[4] & 0x7FFF) - 16383; // how do i keep this number???? 
	printf("conversion.llu %llu\n", temp);
	counter = 63;
	reverse = extract.llu;
	temp >>= 1;
	while (temp != 0)
	{
		reverse <<= 1;
		reverse |= (temp & 1);
		temp >>= 1;
		counter--;
	}
	//reverse <<= counter;
	printf("reverse: %llu\n", reverse);
	return (reverse);
}

int						ft_lowhexpoint(va_list args, t_print *clipb)
{
	unsigned char		buffer[200000];
	t_float				conversion;
	long double			nb;
	int					neg;
	unsigned short		nb_len;

	neg = 1;
	if (ft_floatconv(args, &nb, clipb->flags) == -1)
		neg = -1;
	conversion.llu = ft_extraction(nb);
	printf("conversion.llu %llu\n", conversion.llu);
	nb_len = ft_man_to_buffer(conversion, buffer);
	printf("nblen: %hu\n", nb_len);
	if (ft_lowshrthd_prec(buffer, neg, nb_len, clipb) == -1)
		return (-1);


	// if (flagverif('.', clipb->flags) == 1)
	// 	return (ft_lowshrthd_prec(buffer, neg, nb_len, clipb));
	// if (flagverif('.', clipb->flags) == -1)
	// 	return (ft_lowshrthd_noprec(buffer, neg, nb_len, clipb));
	return (1);
}
