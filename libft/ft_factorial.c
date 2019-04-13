/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_factorial.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 21:26:32 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 20:56:43 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_factorial(int nb)
{
	int h;

	h = nb;
	if (nb == 1 || nb == 0)
		return (1);
	if (nb < 0 || nb > 12)
		return (0);
	while (h != 1)
	{
		h--;
		nb = (nb * h);
	}
	return (nb);
}
