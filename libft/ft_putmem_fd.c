/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putmem_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/05 15:37:04 by aholster       #+#    #+#                */
/*   Updated: 2019/05/22 17:56:23 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putmem_fd(char *mem, size_t len, const int fd)
{
	write(fd, mem, len);
}
