/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:14 by aholster       #+#    #+#                */
/*   Updated: 2019/04/18 16:04:52 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char *format, ...)
{
	va_list ap;
	size_t	len;

	va_start(ap, format);
	if (ft_formatstat(ap, format, &len) == -1)
		return (-1);

	va_end(ap);
}

int	ft_altprintf(char *format, ...)
{
	va_list ap;
	char	*str;
	size_t	len;

	va_start(ap, format);
	if (ft_lstbuffer(ap, format, &str, &len) == -1)
		return (-1);

	va_end(ap);
}
