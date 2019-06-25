/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   float_g.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/17 18:47:57 by aholster       #+#    #+#                */
/*   Updated: 2019/06/17 19:46:47 by aholster      ########   odam.nl         */
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

static int	floatrounder(size_t	index, char *buf)
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

size_t	ft_numput(unsigned long long longcast, unsigned int precision, char *buf)
{
	size_t				index;
	unsigned long long	dup;

	index = 0;
	dup = longcast;
	while (dup > 0)
	{
		dup /= 10;
		index++;
	}
	while (longcast > 0 && index != 0)
	{
		index--;
		buf[index] = (longcast % 10) + '0';
		longcast /= 10;
	}
	dprintf(1, "our long long%s, %c\n", buf, buf[precision]);
	if (index >= precision)
		floatrounder(precision, buf);
	dprintf(1, "our long long%s, %c\n", buf, buf[precision]);
	return (index);
}

int	floatgrap(int precision, double num)
{
	char				buf[150];
	unsigned long long	longcast;
	unsigned int		true_precision;
	size_t				index;

	if (num != num)
		dprintf(1, "NAN\n");
	else if (ft_isinf(num) != 0)
		return (0);
	else
	{
		if (precision < 0)
			true_precision = 6;
		else
			true_precision = precision;
		bzero(buf, 150);
		longcast = (unsigned long long)num;
		num -= longcast;
		index = ft_numput(longcast, true_precision, buf);
		dprintf(1, "%s\n", buf);
	}
	return (0);
}
