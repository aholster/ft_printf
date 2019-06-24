/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   float_testbetter.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/14 18:12:30 by aholster       #+#    #+#                */
/*   Updated: 2019/06/19 18:35:40 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <strings.h>

static int ft_isinf(float f)
{
    long l;
    l = *((long *)&f);
    if (l == 0x7F800000)
	{
		dprintf(1, "INF\n");
        return (1);
	}
    if (l == 0xFF800000)
	{
		dprintf(1, "-INF\n");
        return (-1);
	}
    return (0);
}

static int	roundup(size_t index, char *buf)
{
	if (index > 0)
		index--;
	else
		return (1);
	while (buf[index] == '9' && index != 0)
	{
		buf[index] = '0';
		index--;
	}
	if (buf[index] != '9')
		buf[index]++;
	else
	{
		buf[index] = '0';
		return (1);
	}
	return (0);
}


static int	rounddown(size_t index, char *buf)
{
	if (index > 0)
	{
		index--;
		while (buf[index] == '0' && index != 0)
			index--;
		if (buf[index] != '0')
			buf[index]--;
		else
			return (-1);
	}
	else
	{
		if (buf[0] == '0')
			return (-1);
		else	
			buf--;
	}
	return (0);
}

static int	printfloat(unsigned int precision, double num, char *buf)
{
	unsigned char	subnum;
	size_t			index;

	index = 0;
	while (precision > index)
	{
		num *= 10;
		subnum = (unsigned char)num;
		buf[index] = subnum + '0';
		num -= subnum;
		index++;
	}
//	dprintf(1, "cur subnum %hhu, cur buffer %s\n", subnum, buf);
//	if ((int)(num * 10) >= 5)
//		return (rounddown(precision - 1, buf));
	if (num > 0.5)
		return (roundup(index, buf));
	else if (num > 0.01)
		return (rounddown(index, buf));
	else
	 	return (0);
}

int	floatwrapbetter(int precision, double num)
{
	char				buf[150];
	unsigned long long	longcast;

	if (num != num)
		dprintf(1, "NAN\n");
	else if (ft_isinf(num) != 0)
		return (0);
	else
	{
		bzero(buf, 150);
		if (precision < 0)
			precision = 6;
		longcast = (unsigned long long)num;
		num -= longcast;
		longcast += printfloat(precision, num, buf);
		if (precision != 0)
			dprintf(1, "%llu.%s\n", longcast, buf);
		else
			dprintf(1, "%llu\n", longcast);
	}
	return (0);
}
