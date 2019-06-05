/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_signconv.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 17:03:23 by aholster       #+#    #+#                */
/*   Updated: 2019/06/05 18:14:44 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	va_short(va_list ap, unsigned long long *holder)
{
	short	num;

	num = (short)va_arg(ap, int);
	if (num < 0)
	{
		*holder = (unsigned long long)(-num);
		return (-1);
	}
	else
	{
		*holder = (unsigned long long)num;
		return (0);
	}
}

static int	va_char(va_list ap, unsigned long long *holder)
{
	char	num;

	num = (char)va_arg(ap, int);
	if (num < 0)
	{
		*holder = (unsigned long long)(-num);
		return (-1);
	}
	else
	{
		*holder = (unsigned long long)num;
		return (0);
	}
}

static int	va_long(va_list ap, unsigned long long *holder)
{
	long	num;

	num = (long)va_arg(ap, long);
	if (num < 0)
	{
		*holder = (unsigned long long)(-num);
		return (-1);
	}
	else
	{
		*holder = (unsigned long long)num;
		return (0);
	}
}

static int	va_int(va_list ap, unsigned long long *holder)
{
	int	num;

	num = va_arg(ap, int);
	if (num < 0)
	{
		*holder = (unsigned long long)(-num);
		return (-1);
	}
	else
	{
		*holder = (unsigned long long)num;
		return (0);
	}
}

int			ft_signconv(va_list ap,
		unsigned long long *holder, const t_flag *flags)
{
	long long	num;

	if (flagverif('h', flags) == 1)
		return (va_short(ap, holder));
	else if (doubleverif('h', flags) == 1)
		return (va_char(ap, holder));
	else if (flagverif('l', flags) == 1)
		return (va_long(ap, holder));
	else if (doubleverif('l', flags) == 1)
	{
		num = va_arg(ap, long long);
		if (num < 0)
		{
			*holder = (unsigned long long)(-num);
			return (-1);
		}
		*holder = (unsigned long long)num;
		return (0);
	}
	else
		return (va_int(ap, holder));
}
