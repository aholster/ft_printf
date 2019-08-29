/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_bufmanager.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/20 12:02:33 by jesmith        #+#    #+#                */
/*   Updated: 2019/06/11 16:13:35 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

// void	ft_bufmanager(char *mem, size_t size, t_flag *flags)
// {
// 	static char	biffer[BUFFSIZE];
// 	size_t		temp;
// 	size_t		left;

// 	left = size;
// 	if (mem == NULL)
// 	{
// 		write((*flags).fd, biffer, (*flags).history % BUFFSIZE);
// 		return ;
// 	}
// 	while (left != 0)
// 	{
// 		if ((*flags).history != 0 && (*flags).history % BUFFSIZE == 0)
// 			write((*flags).fd, biffer, BUFFSIZE);
// 		temp = BUFFSIZE - ((*flags).history % BUFFSIZE);
// 		if (left < temp)
// 			temp = left;
// 		ft_memcpy(&biffer[(*flags).history % BUFFSIZE], mem, temp);
// 		mem += temp;
// 		left -= temp;
// 		(*flags).history += temp;
// 	}
// }

// void		ft_flinit(const int fd, t_flag *flags)
// {
// 	(*flags).fd = fd;
// 	(*flags).standflags[0] = 0;
// 	(*flags).standflags[1] = 0;
// 	(*flags).doubleflags[0] = 0;
// 	(*flags).doubleflags[1] = 0;
// 	(*flags).history = 0;
// 	(*flags).precision = 0;
// 	(*flags).padding = 0;
// 	(*flags).history = 0;
// }

// int main(void)
// {
// 	t_flag	flags;
// 	int		fd;
// 	size_t	size;
// 	char	*mem;

// 	fd = 1;
// 	ft_flinit(fd, &flags);
// 	mem = "hello there";
// 	size = 11;
// 	ft_bufmanager(mem, size, &flags);
// 	mem = "something in here";
// 	ft_bufmanager(mem, ft_strlen(mem), &flags);
// 	ft_bufmanager(NULL, 0, &flags);
// 	return (0);
// }