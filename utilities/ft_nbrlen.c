/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nbrlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 13:36:17 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 21:14:08 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_nbrlen(long long n, unsigned int base)
{
	unsigned int length;

	length = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		length++;
	while (n != 0)
	{
		n = n / base;
		length++;
	}
	return (length);
}
