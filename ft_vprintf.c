/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vprintf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 15:19:31 by aholster       #+#    #+#                */
/*   Updated: 2019/09/13 18:20:57 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_vprintf(const char *restrict format, va_list args)
{
	int		holder;

	holder = ft_vdprintf(1, format, args);
	return (holder);
}
