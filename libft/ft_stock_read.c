/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stock_read.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/26 16:44:22 by aholster       #+#    #+#                */
/*   Updated: 2019/04/26 17:27:58 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stock_read(const unsigned char *stock, size_t bitnum)
{
	unsigned short	segment;

	segment = bitnum / 8;
	if ((stock[segment] & (1 << (bitnum - (segment * 8)))) > 0)
		return (1);
	return (0);
}
