/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsignconv.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 18:48:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/11 17:58:35 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	va_short(va_list ap, unsigned long long *holder)
{
	short	num;

	num = (short)va_arg(ap, int);
	if (num >= 0)
	{
		*holder = (unsigned long long)num;
		return (1);
	}
	return (-1);
}

static int	va_char(va_list ap, unsigned long long *holder)
{
	char	num;

	num = (char)va_arg(ap, int);
	if (num >= 0)
	{
		*holder = (unsigned long long)num;
		return (1);
	}
	return (-1);
}

static int	va_long(va_list ap, unsigned long long *holder)
{
	long	num;

	num = (long)va_arg(ap, long);
	if (num >= 0)
	{
		*holder = (unsigned long long)num;
		return (1);
	}
	return (-1);
}

static int	va_int(va_list ap, unsigned long long *holder)
{
	int	num;

	num = va_arg(ap, int);
	if (num >= 0)
	{
		*holder = (unsigned long long)num;
		return (1);
	}
	return (-1);
}

int			ft_unsignconv(va_list ap,\
		unsigned long long *holder, const t_flag *flags)
{
	long long	num;

	if (flagverif('h', flags) == 1)
		return (va_short(ap, holder));
	else if (doubleverif('h', flags) == 1)
		return (va_char(ap, holder));
	else if (flagverif('l', flags) == 1)
		return (va_long(ap, holder));
	else if (doubleverif('l', flags) == 1 || flagverif('L', flags) == 1)
	{
		num = va_arg(ap, long long);
		if (num >= 0)
		{
			*holder = (unsigned long long)num;
			return (1);
		}
		return (-1);
	}
	else
		return (va_int(ap, holder));
}
