/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_del.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/24 13:11:45 by aholster       #+#    #+#                */
/*   Updated: 2019/10/04 18:38:21 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

void	ft_del(void *data, size_t size)
{
	free(data);
	data = NULL;
	size = 0;
}
