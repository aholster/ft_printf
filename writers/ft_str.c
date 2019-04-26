/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 21:38:26 by jesmith        #+#    #+#                */
/*   Updated: 2019/04/26 19:29:30 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
static	unsigned char	*ft_null (void)
{
	char	*new;
	char	*temp;
	size_t 			i;

	i = 0;
	temp =  "(null)";
	new = ft_strnew(7);
	if (new == NULL)
		return (NULL);
	while (temp[i] != '\0')
	{
		new[i] = temp[i];
		i++; 
	}
	return ((unsigned char *)new);
}

void static	swap(int *a, int *b) // make better swap function? 
{
	int h;

	h = *a;
	*a = *b;
	*b = h;
}


static size_t	ft_difference(size_t len, t_print *clipb)
{
	size_t diff;

	if ((size_t)(*clipb).flags->padding > len)
		diff = (size_t)((*clipb).flags->padding - len);
	else
		diff = (size_t)(*clipb).flags->padding;
	return (diff);
}

static int	ft_padmanager(unsigned char *str, size_t len, t_print *clipb)
{
	char	*pad;
	size_t	diff;
	char	c;
	
	// if (((1LLU << '0') & (*clipb).flags->actiflags[0]) > 0) -> needed????? 
	// 	c = '0';
	// else
	c = ' ';
	diff = ft_difference(len, clipb);
	pad = ft_stralloc(diff, c);
	if (pad == NULL)
		return (-1);
	if (((1LLU << '-') & (*clipb).flags->actiflags[0]) == 0)
		swap((int *)str, (int*)pad); // make custom swap solution
	pad = ft_strjoin((char *)str, pad); // instead of strjoin...send to pinter one after the other
		if (pad == NULL)
			return (-1);
	str = (unsigned char*)pad;
	free(pad);
	len = ft_strlen((const char*)str);
	(*clipb).printer(str, len, clipb);
	return (1);
}
static int	ft_premanager(va_list ap, t_print *clipb)
{
	unsigned char	*padstr;
	char			*temp;
	size_t			len;

	padstr = va_arg(ap, unsigned char*);
	if (padstr == NULL)
		padstr = ft_null();
	len = ft_strlen((char const*)padstr);
	if (len > (size_t)(*clipb).flags->precision)	 				// string will not be longer that precision
		len = (size_t)(*clipb).flags->precision;
	if (len < (size_t)(*clipb).flags->precision)					// precision is invalid
		(*clipb).flags->precision = len;
	if ((*clipb).flags->padding > (*clipb).flags->precision) 		// padding will not be longer than string
	{
		temp = ft_strsub((const char*)padstr, 0, (size_t)(*clipb).flags->precision);
		len = ft_strlen((const char*)temp);
		padstr = (unsigned char*)temp;
		ft_padmanager(padstr, len, clipb);
		return (1);
	}
	(*clipb).printer(padstr, len, clipb);
	return (1);
}



int			ft_str(va_list ap, t_print *clipb)
{
	unsigned char	*str;
	size_t			len;

	if ((*clipb).flags->precision != 0)
	{
		if (ft_premanager(ap, clipb) == 1)
			return (1);
	}
	str = va_arg(ap, unsigned char*);
	if (str == NULL)
		str = ft_null();
	len = ft_strlen((char const*)str);
	if ((*clipb).flags->precision == 0 && ((*clipb).flags->padding - (int)len) > 0)
	{
		if (ft_padmanager(str, len, clipb) == 1)
			return (1);
	}
	(*clipb).printer(str, (size_t)len, clipb);
	return (1);
}