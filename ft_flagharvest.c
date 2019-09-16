/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flagharvest.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:22:09 by aholster       #+#    #+#                */
/*   Updated: 2019/09/16 21:29:00 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_num_extract(const char *restrict format,\
				size_t * const index, unsigned int * const destination)
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
}

static int		ft_num_arg_extract(va_list args, size_t * const subdex,\
				unsigned int * const destination)
{
	int				num;

	num = va_arg(args, int);
	*subdex += 1;
	if (num < 0)
	{
		*destination = (-num);
		return (-1);	
	}
	else
	{
		*destination = num;
		return (1);
	}
}

static void		flagflip(const unsigned char c, t_flag * const flags)
{
	unsigned short	flip;

	flip = c / 64;
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

static int		ft_valiflag(const unsigned char c, const t_flag * const flags)
{
	unsigned short	flip;

	if (c >= 128)
		return (-1);
	flip = c / 64;
	if (((1LLU << (c - (flip * 64))) & flags->statiflags[flip]) > 0)
		return (1);
	return (-1);
}

static void		ft_flagreset(t_flag * const flags)
{
	flags->actiflags[0] = 0;
	flags->actiflags[1] = 0;
	flags->actidoubles[0] = 0;
	flags->actidoubles[1] = 0;
	flags->precision = 0;
	flags->padding = 0;
}

void			ft_flagharvest(const char *restrict format,\
								size_t *const aindex, t_print *const clipb)
{
	size_t			subdex;

	subdex = *aindex;
	ft_flagreset(clipb->flags);
	while (ft_valiflag(format[subdex], clipb->flags) > 0)
	{
		flagflip(format[subdex], clipb->flags);
		if (format[subdex] >= '1' && format[subdex] <= '9')
			ft_num_extract(format, &subdex, &clipb->flags->padding);
		else if (format[subdex] == '.')
		{
			subdex++;
			if (format[subdex] == '*')
				ft_num_arg_extract(clipb->args, &subdex, &clipb->flags->precision);
			else
				ft_num_extract(format, &subdex, &clipb->flags->precision);
		}
		else if (format[subdex] == '*')
		{
			if (ft_num_arg_extract(clipb->args, &subdex, &clipb->flags->padding) == -1)
				flagflip('-', clipb->flags);
		}
		else
			subdex++;
	}
	*aindex = subdex;
}
