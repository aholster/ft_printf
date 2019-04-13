/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 16:43:03 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 21:03:03 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	index;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	index = ft_nbrlen((long long)n, 10);
	str = ft_strnew(index);
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -(n);
	}
	while (index > 1 || (index > 0 && str[0] != '-'))
	{
		index--;
		str[index] = ((n % 10) + '0');
		n = n / 10;
	}
	return (str);
}
