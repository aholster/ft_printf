/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vsprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 15:19:34 by aholster       #+#    #+#                */
/*   Updated: 2019/09/18 18:30:35 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

int		ft_vsprintf(char *str, const char *restrict format, va_list args)
{
	int	holder;

	holder = ft_vsnprintf(str, MAX_INT + 1, format, args);
	return (holder);
}
