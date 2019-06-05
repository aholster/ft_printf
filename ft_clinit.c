/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_clinit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/22 20:28:22 by aholster       #+#    #+#                */
/*   Updated: 2019/06/05 19:21:54 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_clinit(t_list **lst, int fd, wrt_ptr printer, t_print *clipb)
{
	clipb->alst = lst;
	clipb->history = 0;
	clipb->current = 0;
	clipb->fd = fd;
	clipb->printer = printer;
	clipb->buffer = (char *)malloc(sizeof(char) * BUFFSIZE);
	if (clipb->buffer == NULL)
		return (-1);
	return (1);
}
