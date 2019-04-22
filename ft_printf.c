/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:14 by aholster       #+#    #+#                */
/*   Updated: 2019/04/22 22:16:24 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_bufmanager(char *mem, size_t size, t_print *clipb)
{
	static char	biffer[BUFFSIZE];
	size_t		temp;
	size_t		left;
	size_t		curpos;

	left = size;
	curpos = (*clipb).history % BUFFSIZE;
	if (mem == NULL)
	{
		write((*clipb).fd, biffer, curpos);
		return (0);
	}
	while (left != 0)
	{
		if ((*clipb).history != 0 && curpos == 0)
			write((*clipb).fd, biffer, BUFFSIZE);
		temp = BUFFSIZE - curpos;
		if (left < temp)
			temp = left;
		ft_memcpy(&biffer[curpos], mem, temp);
		mem += temp;
		left -= temp;
		(*clipb).history += temp;
	}
	return (0);
}

int		ft_printf(char *format, ...)
{
	va_list 	ap;
	t_print 	clipb;

	va_start(ap, format);
	if (ft_clinit(NULL, 1, ft_bufmanager, &clipb) == -1)
		return (-1);
	if (ft_format(ap, format, &clipb) == -1)
	{
		free(clipb.buffer);
		return (-1);
	}
	ft_bufmanager(NULL, 0, &clipb);
	va_end(ap);
	return (66666666);
}

// int	ft_altprintf(char *format, ...)
// {
// 	va_list ap;
// 	char	*str;
// 	size_t	len;

// 	va_start(ap, format);
// 	if (ft_lstbuffer(ap, format, &str, &len) == -1)
// 		return (-1);

// 	va_end(ap);
// }
