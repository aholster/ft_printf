/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoba.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/30 18:25:03 by aholster       #+#    #+#                */
/*   Updated: 2019/01/30 19:59:42 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_base1(int n)
{
	char			*str;

	str = malloc(sizeof(char) * n + 1);
	if (str == NULL)
		return (NULL);
	str[n] = '\0';
	n--;
	while (n >= 0)
	{
		str[n] = '1';
		n--;
	}
	return (str);
}

static void	ft_baseput(char *str, long long num, unsigned int base,\
unsigned int index)
{
	char	*legend;

	legend = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	while (index > 1 || (index > 0 && str[0] != '-'))
	{
		index--;
		str[index] = legend[num % base];
		num = num / base;
	}
}

char		*ft_itoba(int n, unsigned int base)
{
	char			*str;
	unsigned int	index;
	long long		num;

	num = n;
	if (base > 36 || base == 0)
	{
		ft_putendl("BASE NOT SUPPORTED");
		return (NULL);
	}
	if (base == 1)
		return (ft_base1(n));
	index = ft_nbrlen(num, base);
	str = ft_strnew(index);
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		num = -(num);
	}
	ft_baseput(str, num, base, index);
	return (str);
}
