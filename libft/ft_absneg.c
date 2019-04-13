/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_absneg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 22:14:45 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 21:01:54 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

long long	ft_absneg(long long num)
{
	if (num < 0)
		return (num);
	return (-(num));
}
