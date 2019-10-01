/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsignconv.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 18:48:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/01 14:51:36 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

void	ft_unsignconv(va_list args,\
			unsigned long long *const holder,\
			const t_flag *const restrict flags)
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
