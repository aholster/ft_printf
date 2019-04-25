/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 21:38:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/04/25 16:31:27 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
// static int	ft_premanager(va_list ap, t_print *clipb)
// {
// 	unsigned char	*padstr;
// 	int				len;

// 	padstr = va_arg(ap, unsigned char*); 		// typecast as unsigned long long or long long? 
// 	// if (padstr == NULL)
// 	// 	padstr = "(null)";
// 	len = ft_strlen((char const*)padstr); 						// need to check for max len?
// 	if (len > (*clipb).flags->precision)	 		// string will not be longer that precision
// 		len = (*clipb).flags->precision;
// 	if (((*clipb).flags->padding - len) < len) 		// padding is invalide
// 		(*clipb).flags->padding = 0;
// 	if (((*clipb).flags->padding - len) > len) 		// padding will not be longer than string
// 		(*clipb).flags->padding -= len;
// 	if (len < (*clipb).flags->precision) 			// precision is invalid
// 		(*clipb).flags->precision = 0;
// 	(*clipb).printer(padstr, len, clipb);
// 	return (1);
// }


static int	ft_padmanager(unsigned char *str, int len, t_print *clipb)
{
	unsigned char	*pad;
	char			c;

	pad = NULL;
	if ((*clipb).flags->actiflags[0] == 0) // use actiflags better c = ' ' or '0' depending on what actiflags in case flag '0' is activate
		c = 0;
	else
		c = 32;
	if (((*clipb).flags->padding - len) > 0 && (*clipb).flags->actiflags[1] == 1) // ensure '-' flag is off
	{
		printf("c: %c\n", c);
		while ((*clipb).flags->padding > len) // add c to front of str
		{
			*pad = c;
			pad++;
			(*clipb).flags->padding--;
		}
		ft_strcat((char *)str, (char *)pad);
	}
	if (((*clipb).flags->padding - len) > 0 && (*clipb).flags->actiflags[1] == 0) // ensure '-' flag is off
	{
		while ((*clipb).flags->padding > len) //add pad to back of str;
		{
			str[len] = c;
			len++;
		}
	}
	(*clipb).printer(str, len, clipb);
	return (1);
}

int			ft_str(va_list ap, t_print *clipb)
{
	unsigned char	*str;
	int				len;

	// if ((*clipb).flags->precision != 0) 														//if there is precision go to precision manager function
	// {
	// 	if (ft_premanager(ap, clipb) == 1)
	// 		return (1);
	// }
	str = va_arg(ap, unsigned char*);
	// if (str == NULL)
	// 	str = "(null)";
	len = ft_strlen((char const*)str);															// need to check for max len?
	printf("padding: %d\n", ((*clipb).flags->padding));
	if ((*clipb).flags->precision == 0 && ((*clipb).flags->padding - len) > 0)
	{
		printf("here\n");
		if (ft_padmanager(str, len, clipb) == 1)												// padding manager function
			return (1);
	}
	// printf("str: %s\n", str);
	// printf("len: %d\n", len);
	(*clipb).printer(str, (size_t)len, clipb);
	return (1);
}