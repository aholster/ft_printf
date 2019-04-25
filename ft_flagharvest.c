/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flagharvest.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:22:09 by aholster       #+#    #+#                */
/*   Updated: 2019/04/25 14:10:59 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_flagreset(t_flag *flags)
{
	(*flags).actiflags[0] = 0;
	(*flags).actiflags[1] = 0;
	(*flags).actidoubles[0] = 0;
	(*flags).actidoubles[1] = 0;
	(*flags).precision = 0;
	(*flags).padding = 0;
//	(*flags).npadding = 0;
}

static int	ft_valiflag(unsigned char c, t_flag *flags)
{
	if (c >= 128 || c == '\0')
		return (-1);
	// else if (c[0] == c[1])
	// {
	// 	if (c[0] >= 64 &&\
	// 		((1LLU << (c[0] - 64)) & (*flags).statidoubles[1] == 1)) //corrected
	// 		return (1);
	// 	else if ((1LLU << c[0]) & (*flags).statidoubles[0] == 1) //corrected
	// 		return (1);
	// }
	// possibly no longer necesary/could result in false positive or unnecesary slowdown
	else if (c >= 64 && ((1LLU << (c - 64)) & (*flags).statiflags[1]) == 1)
		return (1);
	else if (((1LLU << c) & (*flags).statiflags[0]) == 1)
		return (1);
	return (-1);
}

static void	flagflip(unsigned char c, t_flag *flags)
{
	int	flip;

	flip = (c >= 64);
	if (((1LLU << (c - (flip * 64))) & (*flags).statidoubles[flip]) == 1)
	{
		if (((1LLU << (c - (flip * 64))) & (*flags).actiflags[flip]) == 1)
		{
			(*flags).statidoubles[flip] |= (1LLU << (c - (flip * 64)));
			(*flags).actiflags[flip] ^= (1LLU << (c - (flip * 64)));
		}
		else
		{
			(*flags).actiflags[flip] |= (1LLU << (c - (flip * 64)));
			(*flags).statidoubles[flip] ^= (1LLU << (c - (flip * 64)));
		}
	}
	else if (c >= '9' || c <= '0')
		(*flags).actiflags[flip] |= (1LLU << (c - (flip * 64)));
	else
		return ;
		//in progresss
}

int			ft_flagharvest(unsigned char *format, t_print *clipb)
{
	size_t	index;

	index = 1;
	ft_flagreset((*clipb).flags);
	while (ft_valiflag(format[index], (*clipb).flags) == 1)
	{
		//for statidoubles, increment index another step to avoid valiflag bugging
		flagflip(format[index], (*clipb).flags);

		index++;
	}
	return (index);
}
