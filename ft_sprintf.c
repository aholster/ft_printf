/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sprintf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 15:19:24 by aholster       #+#    #+#                */
/*   Updated: 2019/09/13 18:20:57 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						ft_sprintf(char *str, const char *restrict format, ...)
{
	va_list	args;
	int		holder;

	va_start(args, format);
	holder = ft_vsprintf(str, format, args);
	va_end(args);
	return (holder);
}