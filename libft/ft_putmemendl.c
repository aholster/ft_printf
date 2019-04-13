/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putmemendl.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/05 15:35:31 by aholster       #+#    #+#                */
/*   Updated: 2019/04/05 18:37:32 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putmemendl(char *mem, size_t len)
{
	write(1, mem, len);
}
