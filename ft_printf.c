/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:14 by aholster       #+#    #+#                */
/*   Updated: 2019/04/20 14:17:39 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_bufmanager(char *mem, size_t size, t_flag *flags)
{
	static char	biffer[BUFFSIZE];
	size_t		temp;
	size_t		left;

	left = size;
	if (mem == NULL)
	{
		write((*flags).fd, biffer, (*flags).history % BUFFSIZE);
		return ;
	}
	while (left != 0)
	{
		if ((*flags).history != 0 && (*flags).history % BUFFSIZE == 0)
			write((*flags).fd, biffer, BUFFSIZE);
		temp = BUFFSIZE - ((*flags).history % BUFFSIZE);
		if (left < temp)
			temp = left;
		ft_memcpy(&biffer[(*flags).history % BUFFSIZE], mem, temp);
		mem += temp;
		left -= temp;
		(*flags).history += temp;
	}
}


int	ft_printf(char *format, ...)
{
	va_list ap;
	int		fd;
	t_flag flags;

	fd = 1;
	va_start(ap, format);
	ft_flinit(fd, &flags);
	flags.lst = NULL;

	flags.print = ft_bufmanager;

	if (ft_format(ap, format, &flags) == -1)
		return (-1);

	va_end(ap);
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
