/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprime.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 19:14:10 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 21:02:48 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_isprime(unsigned int num)
{
	unsigned int	counter;

	counter = 2;
	while (counter <= num / counter)
	{
		if (num % counter == 0)
			return (0);
		counter++;
	}
	return (1);
}
