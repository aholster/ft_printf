/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stock_write.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/26 16:44:24 by aholster       #+#    #+#                */
/*   Updated: 2019/04/26 16:57:48 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stock_write(unsigned char *stock, size_t bitnum)
{
	unsigned short	segment;

	segment = bitnum / 8;
	stock[segment] |= (1 << (bitnum - (segment * 8)));
}
