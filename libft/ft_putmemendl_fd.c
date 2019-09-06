/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putmemendl_fd.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/05 15:38:58 by aholster       #+#    #+#                */
/*   Updated: 2019/05/22 17:56:41 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putmemendl_fd(char *mem, size_t len, const int fd)
{
	write(fd, mem, len);
}
