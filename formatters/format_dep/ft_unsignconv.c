/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsignconv.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 18:48:26 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/19 09:41:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

void	ft_unsignconv(va_list args,\
			unsigned long long *const holder,\
			const t_flag *const flags)
{
	if (flg_verif('h', flags) == 1)
		*holder = (unsigned short)va_arg(args, unsigned int);
	else if (flgdbl_verif('h', flags) == 1)
		*holder = (unsigned char)va_arg(args, unsigned int);
	else if (flg_verif('l', flags) == 1)
		*holder = (unsigned long)va_arg(args, unsigned long);
	else if (flgdbl_verif('l', flags) == 1)
		*holder = va_arg(args, unsigned long long);
	else
		*holder = (unsigned int)va_arg(args, unsigned int);
}
