/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putcaret.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/22 17:53:04 by aholster       #+#    #+#                */
/*   Updated: 2019/05/22 18:05:23 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putcaret(int c)
{
	char caret[2];

	if (c < ' ' && c >= 0)
	{
		caret[0] = '^';
		caret[1] = c + '@';
		write(1, caret, 2);
	}
	else if (c == 127)
		write(1, "^?", 2);
	else
		ft_putchar(c);
}
