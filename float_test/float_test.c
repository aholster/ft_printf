/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   float_test.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/14 18:12:30 by aholster       #+#    #+#                */
/*   Updated: 2019/06/24 15:18:02 by aholster      ########   odam.nl         */
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

// static int	rounder(size_t	index, char *buf)
// {
// 	if (index > 0)
// 		index--;
// 	else
// 		return (1);
// 	while (buf[index] == '9' && index != 0)
// 	{
// 		buf[index] = '0';
// 		index--;
// 	}
// 	if (buf[index] != '9')
// 		buf[index]++;
// 	else
// 	{
// 		buf[index] = '0';
// 		return (1);
// 	}
// 	return (0);
// }

static int	rounder(size_t	index, char *buf)
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

static unsigned long long	printfloat(unsigned long long longcast, unsigned int precision, double num, char *buf)
{
	unsigned char subnum;
	size_t	index;

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
	num *= 10;
//	dprintf(1, "rounding deciding number is %d\t", (unsigned char)num);
	if (num > 5)
		return (longcast += rounder(index, buf));
	else if (num == 5)
	{
		if ((longcast & 1) == 1)
			return (longcast + 1);
		else
			return (longcast);
	}
	return (longcast);
}

int	floatwrap(int precision, double num)
{
	char				buf[2000];
	unsigned long long	longcast;

	if (num != num)
		dprintf(1, "NAN\n");
	else if (ft_isinf(num) != 0)
		return (0);
	else
	{
		bzero(buf, sizeof(buf));
		if (precision < 0)
			precision = 6;
		longcast = (unsigned long long)num;
		num -= longcast;
//		longcast += printfloat(precision, num, buf);
		longcast = printfloat(longcast, precision, num, buf);
		if (precision != 0)
			dprintf(1, "%llu.%s\n", longcast, buf);
		else
			dprintf(1, "%llu\n", longcast);
	}
	return (0);
}
