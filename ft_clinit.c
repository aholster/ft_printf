/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_clinit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/22 20:28:22 by aholster       #+#    #+#                */
/*   Updated: 2019/06/07 18:48:21 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_clinit(t_list **alst, int fd, t_wrt_ptr printer, t_print *clipb)
{
	clipb->alst = alst;
	clipb->history = 0;
	clipb->current = 0;
	clipb->fd = fd;
	clipb->printer = printer;
	clipb->buffer = (char *)malloc(sizeof(char) * BUFFSIZE);
	if (clipb->buffer == NULL)
		return (-1);
	return (1);
}
