/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_statbuf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 19:57:30 by aholster       #+#    #+#                */
/*   Updated: 2019/04/18 17:46:12 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_bufmanager(char input, t_statbuf buffer)
{
	buffer.store[buffer.cur] = input;
	buffer.cur += 1;
	if (buffer.cur == 50)
	{
		write(1, &buffer.store, 50);
		buffer.history += cur;
		buffer.cur = 0;
	}
}

int		ft_formatstat(va_list ap, char *format, size_t *len)
{
	size_t		index;
	t_statbuf	buffer;
	t_flag		flags;
	int			functbl[53];

	index = 0;
	buffer.cur = 0;
	buffer.history = 0;
	ft_flinit(ap, &flags);
	while (format[index] != '\0')
	{
		if (format[index] == '%')
		{
			index += ft_flagharvest(&format[index], &flags);
			if (ft_dispatcher(&format[index], functbl, &buffer, &flags) == -1)
				return (-1);
		}
		else
			ft_bufmanager(format[index], buffer);
		index++;
	}
	return (1);
}
