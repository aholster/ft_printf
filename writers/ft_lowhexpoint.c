/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowhexpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/28 14:42:40 by jesmith        #+#    #+#                */
/*   Updated: 2019/08/30 18:11:07 by jesmith       ########   odam.nl         */
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

static int				exponentbuffer(t_print *clipb, unsigned short expon, long double nb)
{
	unsigned char	buffer[8];
	size_t			index;

	index = 1;
	buffer[0] = 'p';
	if (nb < 1)
		buffer[index] = '-';
	else
		buffer[index] = '+';
	index++;
	if (expon == 0)
	{
		buffer[index] = '0';
		index++;
	}
	while (expon > 0)
	{
		buffer[index] = ((expon % 10) + '0');
		expon /= 10;
		index++;
	}
	buffer[index] = expon;
	if (clipb->printer(buffer, (size_t)index, clipb) == -1)
		return (-1);
	return (1);
 }

static int				ft_lowshrthd_prec(unsigned char *buffer, int neg, \
					unsigned short expon, t_print *clipb, long double nb)
{
	unsigned short nb_len;

	nb_len = ft_strlen((const char *)buffer);
	if (flagverif('-', clipb->flags) == -1 && flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (ft_signhand(neg, clipb) == -1)
		return (-1);
	if (clipb->printer((const unsigned char *)"0x", 4, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == -1 && flagverif('0', clipb->flags) == 1)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, nb_len, clipb) == -1)
		return (-1);
	if (clipb->flags->precision > nb_len && flagverif('.', clipb->flags) == 1)
		if (ft_zero_padder(clipb->flags->precision - nb_len, clipb) == -1)
			return (-1);
	if (exponentbuffer(clipb, expon, nb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > nb_len) // this is for no prec see if works here 
		if (ft_space_padder(nb_len, clipb) == -1)
			return (-1);
	if (flagverif('-', clipb->flags) == -1 && flagverif('0', clipb->flags) == 1)
		if (ft_zero_padder(nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static void				ft_man_to_buffer(t_float conversion, unsigned char *buffer)
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
	//conversion.shrt[cur_len] = (temp % 16) + '0';
	while (temp > 16)
	{
		buffer[cur_len] = base[(temp % 16)];
		temp /= 16;
		cur_len--;
	}
	buffer[cur_len] = base[temp];
}

// static unsigned long long			ft_extraction(t_float extract)
// {

// 	unsigned char		counter;
// 	unsigned long long	reverse;
// 	unsigned long long	temp;

// 	temp = extract.llu;
// 	printf("conversion.llu %llx\n", temp);
// 	counter = 63;
// 	reverse = temp;
// 	temp >>= 1;
// 	while (temp != 0)
// 	{
// 		reverse <<= 1;
// 		reverse |= (temp & 1);
// 		temp >>= 1;
// 		counter--;
// 	}
// 	//reverse ^= (temp & 1);
// 	//reverse = reverse ^ 1;
// 	//reverse <<= 2;
// 	reverse <<= counter;
// 	printf("after reversed %llx\n", reverse);
// 	return (reverse);
// }

int						ft_lowhexpoint(va_list args, t_print *clipb)
{
	unsigned char		buffer[16];
	t_float				conversion;
	long double			nb;
	int					neg;
	unsigned short		expon;


	neg = ft_floatconv(args, &nb, clipb->flags);
	conversion.ld = nb;
	// conversion.llu <<= 1;
	expon = (conversion.shrt[4] & 0x7FFF) - 16383;
	//conversion.llu = ft_extraction(conversion);
	ft_man_to_buffer(conversion, buffer);
	if (ft_lowshrthd_prec(buffer, neg, expon, clipb, nb) == -1)
		return (-1);
	// if (flagverif('.', clipb->flags) == 1)
	// 	return (ft_lowshrthd_prec(buffer, neg, nb_len, clipb));
	// if (flagverif('.', clipb->flags) == -1)
	// 	return (ft_lowshrthd_noprec(buffer, neg, nb_len, clipb));
	return (1);
}
