/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dprintf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 15:19:28 by aholster       #+#    #+#                */
/*   Updated: 2019/09/13 17:24:36 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_dprintf(const int fd, const char * restrict format, ...)
{
	va_list		args;
	int			holder;

	va_start(args, format);
	holder = ft_vdprintf(fd, format, args);
	va_end(args);
	return (holder);
}
