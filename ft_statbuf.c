/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_statbuf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 19:57:30 by aholster       #+#    #+#                */
/*   Updated: 2019/04/19 16:42:43 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_formatstat(va_list ap, char *format, size_t *len, const int fd)
{
	size_t		index;
	t_flag		flags;
	void		*functbl[53];

	index = 0;
	ft_flinit(fd, &flags);
	while (format[index] != '\0')
	{
		if (format[index] == '%')
		{
			index += ft_flagharvest(&format[index], &flags);
			if (ft_dispatcher(ap, &format[index], functbl, &flags) == -1)
				return (-1);
		}
		else
			ft_bufmanager(format, 1, &flags);
		index++;
	}
	return (1);
}
