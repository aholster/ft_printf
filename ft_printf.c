/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:14 by aholster       #+#    #+#                */
/*   Updated: 2019/04/26 17:36:39 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_bufmanager(unsigned char *mem, size_t size, t_print *clipb)
{
	static char	biffer[BUFFSIZE];
	size_t		left;
	size_t		temp;

	left = size;
	if (mem == NULL)
	{
		write((*clipb).fd, biffer, (*clipb).current);
		return (0);
	}
	while (left != 0)
	{
		if ((*clipb).current == BUFFSIZE)
		{
			write((*clipb).fd, biffer, BUFFSIZE);
			(*clipb).current = 0;
		}
		if (size + (*clipb).current < BUFFSIZE)
			temp = size;
		else
			temp = ft_constrain(size, 0, BUFFSIZE); // ft_constrain(int, int, int) implicit cast
		ft_memcpy(&biffer[(*clipb).current], mem, temp);
		(*clipb).current += temp;
		left -= temp;
	}
	(*clipb).history += size;
	return (0);
}

int		ft_printf(char *format, ...)
{
	va_list 	ap;
	t_print 	clipb;

	va_start(ap, format);
	if (ft_clinit(NULL, 1, ft_bufmanager, &clipb) == -1)
		return (-1);
	if (ft_format(ap, (unsigned char *)format, &clipb) == -1)
	{
		free(clipb.buffer);
		return (-1);
	}
	ft_bufmanager(NULL, 0, &clipb);
	va_end(ap);
	return (clipb.history);
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
