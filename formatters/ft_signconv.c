/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_signconv.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 17:03:23 by aholster       #+#    #+#                */
/*   Updated: 2019/10/01 19:27:30 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int	va_short(va_list args, unsigned long long *const restrict holder)
{
	short	num;

	num = (short)va_arg(args, int);
	if (num < 0)
	{
		*holder = ((-num) & 0xFFFF);
		return (-1);
	}
	else
	{
		*holder = num;
		return (0);
	}
}

static int	va_char(va_list args, unsigned long long *const restrict holder)
{
	char	num;

	num = (char)va_arg(args, int);
	if (num < 0)
	{
		*holder = ((-num) & 0xFF);
		return (-1);
	}
	else
	{
		*holder = num;
		return (0);
	}
}

static int	va_long(va_list args, unsigned long long *const restrict holder)
{
	long	num;

	num = (long)va_arg(args, long);
	if (num < 0)
	{
		*holder = ((-num) & 0xFFFFFFFF);
		return (-1);
	}
	else
	{
		*holder = num;
		return (0);
	}
}

static int	va_int(va_list args, unsigned long long *const restrict holder)
{
	int	num;

	num = va_arg(args, int);
	if (num < 0)
	{
		*holder = ((-num) & 0xFFFFFFFF);
		return (-1);
	}
	else
	{
		*holder = num;
		return (0);
	}
}

int			ft_signconv(va_list args,\
				unsigned long long *const restrict holder,\
				const t_flag *const restrict flags)
{
	long long	num;

	if (flagverif('h', flags) == 1)
		return (va_short(args, holder));
	else if (doubleverif('h', flags) == 1)
		return (va_char(args, holder));
	else if (flagverif('l', flags) == 1)
		return (va_long(args, holder));
	else if (doubleverif('l', flags) == 1 || flagverif('L', flags) == 1)
	{
		num = va_arg(args, long long);
		if (num < 0)
		{
			*holder = ((-num) & 0xFFFFFFFFFFFFFFFF);
			return (-1);
		}
		*holder = num;
		return (0);
	}
	else
		return (va_int(args, holder));
}