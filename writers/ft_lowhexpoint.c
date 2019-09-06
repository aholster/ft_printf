/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lowhexpoint.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/28 14:42:40 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/06 10:47:59 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int				exponentbuffer(t_print *clipb, short expon)
{
	unsigned char	buffer[8];
	size_t			index;
	int				neg;

	neg = expon;
	index = (size_t)ft_nbrlen((long long)expon, 10);
	if (expon < 0)
		expon *= -1;
	while (index > 1)
	{
		buffer[index] = (expon % 10) + '0';
		index--;
		expon /= 10;
	}
	if (neg < 0)
		buffer[1] = '-';
	else
		buffer[1] = '+';
	buffer[0] = 'p';
	if (clipb->printer(buffer, index + 2, clipb) == -1)
		return (-1);
	return (1);
}

static int				ft_lowshrthd_pad(unsigned char *buffer, \
					short expon, t_print *clipb, unsigned short str_len)
{
	unsigned short	nb_len;

	nb_len = ft_nbrlen((long long)expon, 10);
	if (flagverif('-', clipb->flags) == -1 && \
	flagverif('0', clipb->flags) == -1)
		if (ft_space_padder(str_len + 2 + nb_len, clipb) == -1)
			return (-1);
	if (ft_prefix((int)str_len, clipb) == -1)
		return (-1);
	if (clipb->printer((const unsigned char *)"0x", 2, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == -1 && flagverif('0', clipb->flags) == 1)
		if (ft_zero_padder(str_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, str_len, clipb) == -1)
		return (-1);
	if (clipb->flags->precision > str_len && flagverif('.', clipb->flags) == 1)
		if (ft_zero_padder(str_len - 2, clipb) == -1)
			return (-1);
	if (exponentbuffer(clipb, expon) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1 && clipb->flags->padding > str_len)
		if (ft_space_padder(str_len + 2 + nb_len, clipb) == -1)
			return (-1);
	return (1);
}

static int				ft_lowshrthd_prec(unsigned char *buffer, t_print *clipb)
{
	unsigned short	str_len;
	size_t			dec_len;
	size_t			index;

	index = 0;
	dec_len = 0;
	str_len = ft_strlen((const char *)buffer);
	if (flagverif(' ', clipb->flags) == 1)
		str_len++;
	while (buffer[index] != '\0')
	{
		if (buffer[index] == '.')
		{
			while (buffer[index] != '\0')
			{
				dec_len++;
				index++;
			}
		}
		index++;
	}
	if (flagverif('.', clipb->flags) == 1)
		if (dec_len > clipb->flags->precision && dec_len < str_len)
			str_len = (str_len - dec_len - 1) + clipb->flags->precision;
	return (str_len);
}

static void			ft_man_to_buffer(unsigned long long mantissa, \
				unsigned char *buffer, t_print *clipb)
{
	char				*base;
	unsigned short		cur_len;
	size_t				yes;
	unsigned long long	temp;

	base = "0123456789abcdef";
	yes = 0;
	temp = mantissa;
	cur_len = 0;
	while (temp != 0)
	{
		temp /= 16;
		cur_len++;
	}
	while (mantissa > 16)
	{
		if ((base[(mantissa % 16)] == '0' && yes != 0) || base[(mantissa % 16)] != '0')
		{
			buffer[cur_len] = base[(mantissa % 16)];
			yes++;
		}
		if (cur_len == 2 && (buffer[cur_len + 1] != '\0'|| flagverif('.', clipb->flags) == 1))
		{
			cur_len--;
			buffer[cur_len] = '.';
		}
		mantissa /= 16;
		cur_len--;
	}
	buffer[cur_len] = base[mantissa];
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
	unsigned char		buffer[20];
	t_float				conversion;
	long double			nb;
	unsigned short		str_len;
	short				expon;

	str_len = ft_floatconv(args, &nb, clipb->flags);
	conversion.ld = nb;
	ft_man_to_buffer(conversion.llu, buffer, clipb);
	expon = (conversion.shrt[4] & 0x7FFF) - 16386;
	str_len *= ft_lowshrthd_prec(buffer, clipb);
	if (ft_lowshrthd_pad(buffer, expon, clipb, str_len) == -1)
		return (-1);
	return (1);
}
