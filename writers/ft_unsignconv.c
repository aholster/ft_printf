/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsignconv.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 18:48:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/16 20:51:59 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

// static void		va_short(va_list args, unsigned long long *holder)
// {
// 	short	num;

// 	num = (short)va_arg(args, int);
// 	if (num >= 0)
// 		*holder = (unsigned long long)num;
// }

// static void		va_char(va_list args, unsigned long long *holder)
// {
// 	char	num;

// 	num = (char)va_arg(args, int);
// 	if (num >= 0)
// 		*holder = (unsigned long long)num;
// }

// static void		va_long(va_list args, unsigned long long *holder)
// {
// 	long	num;

// 	num = (long)va_arg(args, long);
// 	if (num >= 0)
// 		*holder = (unsigned long long)num;
// }

// static void		va_int(va_list args, unsigned long long *holder)
// {
// 	int	num;

// 	num = va_arg(args, int);
// 	if (num >= 0)
// 		*holder = (unsigned long long)num;
// }

// void			ft_unsignconv(va_list args,\
// 		unsigned long long *holder, const t_flag *flags)
// {
// 	long long	num;

// 	if (flagverif('h', flags) == 1)
// 		va_short(args, holder);
// 	else if (doubleverif('h', flags) == 1)
// 		va_char(args, holder);
// 	else if (flagverif('l', flags) == 1)
// 		va_long(args, holder);
// 	else if (doubleverif('l', flags) == 1 || flagverif('L', flags) == 1)
// 	{
// 		num = va_arg(args, long long);
// 		if (num >= 0)
// 			*holder = (unsigned long long)num;
// 	}
// 	else
// 		va_int(args, holder);
// }


void			ft_unsignconv(va_list args,\
		unsigned long long *const holder, const t_flag *const flags)
{
	if (flagverif('h', flags) == 1)
		*holder = (unsigned short)va_arg(args, unsigned int);
	else if (doubleverif('h', flags) == 1)
		*holder = (unsigned char)va_arg(args, unsigned int);
	else if (flagverif('l', flags) == 1)
		*holder = (unsigned long)va_arg(args, unsigned long);
	else if (doubleverif('l', flags) == 1 || flagverif('L', flags) == 1)
		*holder = va_arg(args, unsigned long long);
	else
		*holder = (unsigned int)va_arg(args, unsigned int);
}