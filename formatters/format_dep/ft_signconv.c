/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_signconv.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 17:03:23 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 09:41:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"
#include <limits.h>

static int	va_short(va_list args, unsigned long long *const holder)
{
	short	num;

	num = (short)va_arg(args, int);
	if (num < 0)
	{
		*holder = ((-num) & USHRT_MAX);
		return (-1);
	}
	else
	{
		*holder = num;
		return (0);
	}
}

static int	va_char(va_list args,\
				unsigned long long *const holder,\
				const t_flag *const flags)
{
	char	num;

	num = (char)va_arg(args, int);
	if (num < 0)
	{
		*holder = ((-num) & UCHAR_MAX);
		if (num == -128 && flg_verif('l', flags) == 1)
			return (1);
		return (-1);
	}
	else
	{
		*holder = num;
		return (0);
	}
}

static int	va_long(va_list args, unsigned long long *const holder)
{
	long	num;

	num = (long)va_arg(args, long);
	if (num < 0)
	{
		*holder = ((-num) & ULONG_MAX);
		return (-1);
	}
	else
	{
		*holder = num;
		return (0);
	}
}

static int	va_int(va_list args, unsigned long long *const holder)
{
	int	num;

	num = va_arg(args, int);
	if (num < 0)
	{
		*holder = ((-num) & UINT_MAX);
		return (-1);
	}
	else
	{
		*holder = num;
		return (0);
	}
}

int			ft_signconv(va_list args,\
				unsigned long long *const holder,\
				const t_flag *const flags)
{
	long long	num;

	if (flg_verif('h', flags) == 1)
		return (va_short(args, holder));
	else if (flgdbl_verif('h', flags) == 1)
		return (va_char(args, holder, flags));
	else if (flg_verif('l', flags) == 1)
		return (va_long(args, holder));
	else if (flgdbl_verif('l', flags) == 1)
	{
		num = va_arg(args, long long);
		if (num < 0)
		{
			*holder = ((-num) & ULONG_MAX);
			return (-1);
		}
		else
		{
			*holder = num;
			return (0);
		}
	}
	else
		return (va_int(args, holder));
}
