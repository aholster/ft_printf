/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flagharvest.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:22:09 by aholster       #+#    #+#                */
/*   Updated: 2019/06/11 18:12:22 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_num_extract(const unsigned char *format, unsigned int *destination)
{
	size_t			index;
	unsigned int	num;

	index = 0;
	num = 0;
	while (ft_isdigit(format[index]) == 1)
	{
		num = (format[index] - '0') + num;
		if (ft_isdigit(format[index + 1]) == 1)
			num = (num * 10);
		index++;
	}
	*destination = num;
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

	if (c >= 128)
		return (-1);
	flip = c / 64;
	if (((1LLU << (c - (flip * 64))) & flags->statiflags[flip]) > 0)
		return (1);
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
		else if (format[index] >= '1' && format[index] <= '9')
			index += ft_num_extract(format + index, &clipb->flags->padding);
		else if (format[index] == '.')
		{
			clipb->flags->actiflags[flip] |= (1LLU << (format[index] - (flip * 64)));
			index += ft_num_extract(format + index + 1, &clipb->flags->precision);
		}
		else
		{
			clipb->flags->actiflags[flip] |= (1LLU << (format[index] - (flip * 64)));
			index++;
		}
	}
	index++;
	return (index);
}
