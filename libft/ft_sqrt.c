/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sqrt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 21:43:31 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 21:16:49 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int count;

	if (nb < 0)
		return (0);
	count = 0;
	while (count * count <= nb)
	{
		if (count * count == nb)
			return (count);
		count++;
	}
	return (0);
}
