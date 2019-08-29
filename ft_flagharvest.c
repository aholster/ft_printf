/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flagharvest.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:22:09 by aholster       #+#    #+#                */
/*   Updated: 2019/06/25 10:56:04 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_num_extract(const unsigned char *format, size_t *index, unsigned int *destination)
{
	size_t			subdex;
	unsigned int	num;

	subdex = *index;
	num = 0;
	while (ft_isdigit(format[subdex]) == 1)
	{
		num = (format[subdex] - '0') + num;
		if (ft_isdigit(format[subdex + 1]) == 1)
			num = (num * 10);
		subdex++;
	}
	*destination = num;
	*index = subdex;
	// return (index);
}

static void		flagflip(const unsigned char c, t_flag *flags, const unsigned short flip)
{
	if ((((1LLU << (c - (flip * 64))) & flags->statidoubles[flip]) > 0))
	{
		if (((1LLU << (c - (flip * 64))) & flags->actiflags[flip]) > 0)
		{
			flags->actidoubles[flip] |= (1LLU << (c - (flip * 64)));
			flags->actiflags[flip] ^= (1LLU << (c - (flip * 64)));
		}
		else
		{
			flags->actiflags[flip] |= (1LLU << (c - (flip * 64)));
			flags->actidoubles[flip] ^= (1LLU << (c - (flip * 64)));
		}
	}
	else
		flags->actiflags[flip] |= (1LLU << (c - (flip * 64)));
}

static int		ft_valiflag(const unsigned char c, const t_flag *flags)
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

size_t			ft_flagharvest(const unsigned char *format, t_print *clipb)
{
	size_t			index;
	unsigned short	flip;

	index = 1;
	ft_flagreset(clipb->flags);
	while (ft_valiflag(format[index], clipb->flags) > 0)
	{
		flip = format[index] / 64;
		flagflip(format[index], clipb->flags, flip);
		if (format[index] >= '1' && format[index] <= '9')
		{
			// index += ft_num_extract(format + index, &clipb->flags->padding);
			ft_num_extract(format, &index, &clipb->flags->padding);
		}
		else if (format[index] == '.')
		{
			// index += ft_num_extract(format + index + 1, &clipb->flags->precision) + 1;
			index++;
			ft_num_extract(format, &index, &clipb->flags->precision);
		}
		else
			index++;
	}
	return (index);
}
