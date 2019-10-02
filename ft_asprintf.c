/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_asprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 19:47:52 by aholster       #+#    #+#                */
/*   Updated: 2019/10/02 17:42:40 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

int			ft_asprintf(char **ret, const char *restrict format, ...)
{
	va_list		args;
	int			holder;

	va_start(args, format);
	holder = ft_vasprintf(ret, format, args);
	va_end(args);
	return (holder);
}
