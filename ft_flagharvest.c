/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flagharvest.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:22:09 by aholster       #+#    #+#                */
/*   Updated: 2019/05/21 17:52:35 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_precision(unsigned char *format, t_print *clipb)
{
	char	*sub;
	size_t	index;
	size_t	len;
	size_t	start;

	index = 0;
	len = 0;
	index++;
	start = index;
	while (format[index] <= '9' && format[index] >= '0')
	{
		len++;
		index++;
	}
	sub = ft_strsub((const char*)format, start, len);
	clipb->flags->precision = ft_atoi(sub);
	free(sub);
	return (index);
}

static size_t	ft_padextract(unsigned char *format, t_print *clipb)
{
	char	*sub;
	size_t	index;

	index = 0;
	while (format[index] <= '9' && format[index] >= '0')
		index++;
	sub = ft_strsub((const char*)format, 0, index);
	clipb->flags->padding = ft_atoi(sub);
	free(sub);
	return (index);
}

static void		flagflip(unsigned char c, t_flag *flags, unsigned short flip)
{
	if (((1LLU << (c - (flip * 64))) & flags->actiflags[flip]) == 1)
	{
		flags->statidoubles[flip] |= (1LLU << (c - (flip * 64)));
		flags->actiflags[flip] ^= (1LLU << (c - (flip * 64)));
	}
	else
	{
		flags->actiflags[flip] |= (1LLU << (c - (flip * 64)));
		flags->statidoubles[flip] ^= (1LLU << (c - (flip * 64)));
	}
}

static int		ft_valiflag(unsigned char c, t_flag *flags)
{

	unsigned short	flip;

	if (c >= 128 || c == '\0')
		return (-1);
	// else if (c[0] == c[1])
	// {
	// 	if (c[0] >= 64 &&\
	// 		((1LLU << (c[0] - 64)) & flags->statidoubles[1] == 1)) //corrected
	// 		return (1);
	// 	else if ((1LLU << c[0]) & flags->statidoubles[0] == 1) //corrected
	// 		return (1);
	// }
	// possibly no longer necesary/could result in false positive or unnecesary slowdown
	flip = c / 64;
	if (((1LLU << (c - (flip * 64))) & flags->statiflags[flip]) > 0)
		return (1);
//	if (c >= 64 && ((1LLU << (c - 64)) & flags->statiflags[1]) == 0)
//		return (1);
	// (((1LLU << c) & flags->statiflags[0])) ? printf("True\n") : printf("False\n");
//	if (((1LLU << c) & flags->statiflags[0]) > 0)
//		return (1);
	return (-1);
}

static void		ft_flagreset(t_flag *flags)
{
	flags->actiflags[0] = 0;
	flags->actiflags[1] = 0;
	flags->actidoubles[0] = 0;
	flags->actidoubles[1] = 0;
	flags->precision = 0;
	flags->padding = 0;
//	flags->npadding = 0;
}

size_t			ft_flagharvest(unsigned char *format, t_print *clipb) // index incrementing problems
{
	size_t			index;
	unsigned short	flip;

	index = 0;
	ft_flagreset(clipb->flags);
	while (ft_valiflag(format[index], clipb->flags) > 0)
	{
		flip = format[index] / 64;
		if (((1LLU << (format[index] - (flip * 64))) & clipb->flags->statidoubles[flip]) == 0)
			flagflip(format[index], clipb->flags, flip);
		if (format[index] >= '1' && format[index] <= '9')
			index += ft_padextract(&format[index], clipb);
		else if (format[index] == '.')
			index += ft_precision(&format[index], clipb);
		else
		{
			clipb->flags->actiflags[flip] |= (1LLU << (format[index] - (flip * 64)));
			index++;
		}
		// index++;
	}
	index++; //here 
	return (index);
}
