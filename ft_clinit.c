/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_clinit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/22 20:28:22 by aholster       #+#    #+#                */
/*   Updated: 2019/04/24 17:07:42 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_clinit(t_list **lst, int fd,\
			int (*printer)(unsigned char*, size_t, t_print*), t_print *clipb)
{
	(*clipb).alst = lst;
	(*clipb).history = 0;
	(*clipb).fd = fd;
	(*clipb).printer = printer;
	(*clipb).buffer = (char *)malloc(sizeof(char) * BUFFSIZE);
	if ((*clipb).buffer == NULL)
		return (-1);
	return (1);
}
