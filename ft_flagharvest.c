/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flagharvest.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:22:09 by aholster       #+#    #+#                */
/*   Updated: 2019/10/01 19:08:30 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/ft_internals.h"

static void		ft_num_extract(const char *const restrict format,\
					size_t *const restrict index,\
					unsigned int *const restrict destination)
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

static int		ft_num_arg_extract(va_list args,\
					size_t *const restrict subdex,\
					unsigned int *const restrict destination)
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

static void		flagflip(const unsigned char c, t_flag *const restrict flags)
{
	const unsigned short	flip = c / FLG_UNS;

	if ((((1LLU << (c - (flip * FLG_UNS))) & flags->statidoubles[flip]) > 0))
	{
		if (((1LLU << (c - (flip * FLG_UNS))) & flags->actiflags[flip]) > 0)
		{
			flags->actidoubles[flip] |= (1LLU << (c - (flip * FLG_UNS)));
			flags->actiflags[flip] ^= (1LLU << (c - (flip * FLG_UNS)));
		}
		else
		{
			flags->actiflags[flip] |= (1LLU << (c - (flip * FLG_UNS)));
			flags->actidoubles[flip] ^= (1LLU << (c - (flip * FLG_UNS)));
		}
	}
	else
		flags->actiflags[flip] |= (1LLU << (c - (flip * FLG_UNS)));
}

static int		ft_valiflag(const unsigned char c,\
					const t_flag *const restrict flags)
{
	const unsigned short	flip = c / FLG_UNS;

	if (c >= 128)
		return (-1);
	if (((1LLU << (c - (flip * FLG_UNS))) & flags->statiflags[flip]) > 0)
		return (1);
	return (-1);
}

static void		ft_flagreset(t_flag *const restrict flags)
{
	// flags->actiflags[0] = 0;
	// flags->actiflags[1] = 0;
	// flags->actiflags[2] = 0;
	// flags->actiflags[3] = 0;
	// flags->actidoubles[0] = 0;
	// flags->actidoubles[1] = 0;
	// flags->actidoubles[2] = 0;
	// flags->actidoubles[3] = 0;
	ft_bzero(flags->actiflags, 16);
	ft_bzero(flags->actidoubles, 16);
	flags->precision = 0;
	flags->padding = 0;
}

void			ft_flagharvest(const char *restrict format,\
					size_t *const aindex,\
					t_writer *const restrict clipb)
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
