/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_statbuf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 19:57:30 by aholster       #+#    #+#                */
/*   Updated: 2019/04/19 18:57:04 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_format(va_list ap, char *format, t_flag *flags)
{
	size_t		index;
	void		*functbl[53];

	index = 0;
	while (format[index] != '\0')
	{
		if (format[index] == '%')
		{
			index += ft_flagharvest(&format[index], flags);
			if (ft_dispatcher(ap, &format[index], functbl, flags) == -1)
				return (-1);
		}
		else
			ft_bufmanager(format, sizeof(char), flags);
		index++;
	}
	return (1);
}
