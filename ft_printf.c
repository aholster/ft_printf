/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:14 by aholster       #+#    #+#                */
/*   Updated: 2019/06/19 15:35:01 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(const char *format, ...)
{
	va_list		args;
	int			ret;

	va_start(args, format);
	ret = ft_vdprintf(1, format, args);
	va_end(args);
	return (ret);
}

int			ft_dprintf(const int fd, const char *format, ...)
{
	va_list		args;
	int			ret;

	va_start(args, format);
	ret = ft_vdprintf(fd, format, args);
	va_end(args);
	return (ret);
}

int			ft_vprintf(const char *format, va_list args)
{
	int			ret;

	ret = ft_vdprintf(1, format, args);
	return (ret);
}
