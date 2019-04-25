/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flagharvest.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:22:09 by aholster       #+#    #+#                */
/*   Updated: 2019/04/25 20:17:24 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_padextract(unsigned char *format, size_t index, t_print *clipb)
{
	unsigned char	count;
	int				num;

	count = 0;
	while (format[index] <= '9' && format[index] >= '0')
	{
		if (format[index] <= '9')
		{
			num = 0;
			count = (char)format[index];
			while (count > '0')
			{
				num++;
				count--;
			}
			(*clipb).flags->padding = (*clipb).flags->padding + num;
			if (format[index + 1] <= '9' && format[index + 1] >= '0')
				(*clipb).flags->padding *= 10;
		}
		index++;
	}
	return (index);
}

static void		flagflip(unsigned char c, t_flag *flags, unsigned short flip)
{
	if (((1LLU << (c - (flip * 64))) & (*flags).actiflags[flip]) == 1)
	{
		(*flags).statidoubles[flip] |= (1LLU << (c - (flip * 64)));
		(*flags).actiflags[flip] ^= (1LLU << (c - (flip * 64)));
	}
	else
	{
		(*flags).actiflags[flip] |= (1LLU << (c - (flip * 64)));
		(*flags).statidoubles[flip] ^= (1LLU << (c - (flip * 64)));
	}
}

static int		ft_valiflag(unsigned char c, t_flag *flags)
{
	if (c >= 128 || c == '\0')
		return (-1);
	// else if (c[0] == c[1])
	// {
	// 	if (c[0] >= 64 &&\
	// 		((1LLU << (c[0] - 64)) & (*flags).statidoubles[1] == 1)) //corrected
	// 		return (1);
	// 	else if ((1LLU << c[0]) & (*flags).statidoubles[0] == 1) //corrected
	// 		return (1);
	// }
	// possibly no longer necesary/could result in false positive or unnecesary slowdown
	if (c >= 64 && ((1LLU << (c - 64)) & (*flags).statiflags[1]) == 1)
		return (1);
	// (((1LLU << c) & (*flags).statiflags[0])) ? printf("True\n") : printf("False\n");
	if (((1LLU << c) & (*flags).statiflags[0]) > 0)
		return (1);
	return (-1);
}

static void		ft_flagreset(t_flag *flags)
{
	(*flags).actiflags[0] = 0;
	(*flags).actiflags[1] = 0;
	(*flags).actidoubles[0] = 0;
	(*flags).actidoubles[1] = 0;
	(*flags).precision = 0;
	(*flags).padding = 0;
//	(*flags).npadding = 0;
}

size_t			ft_flagharvest(unsigned char *format, t_print *clipb)
{
	size_t			index;
	unsigned short	flip;

	index = 0;
	ft_flagreset((*clipb).flags);
	while (ft_valiflag(format[index], (*clipb).flags) == 1)
	{
		flip = format[index] / 64;
		if (((1LLU << (format[index] - (flip * 64))) \
			& (*clipb).flags->statidoubles[flip]) == 1)
			flagflip(format[index], (*clipb).flags, flip);
		else if (format[index] >= '1' || format[index] <= '9')
		{
			index = ft_padextract(format, index, clipb);
		}
		else
		{
			((*clipb).flags->actiflags[flip] |= \
			(1LLU << (format[index] - (flip * 64))));
		}
		index++;
		//for statidoubles, increment index another step to avoid valiflag bugging
	}
	return (index);
}
