/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mantissa_to_numlst.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/28 18:10:51 by aholster       #+#    #+#                */
/*   Updated: 2019/09/06 08:18:33 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

static unsigned long long	ft_llurev(unsigned long long numa)
{
	unsigned char		counter;
	unsigned long long	reverse_num;

	counter = 63;
	reverse_num = numa;
	numa >>= 1;
	while (numa != 0)
	{
		reverse_num <<= 1;
		reverse_num |= (numa & 1);
		numa >>= 1;
		counter--;
	}
	reverse_num <<= counter;
	return (reverse_num);
}

static int					ft_mant_to_lst(t_numlst *lstrav,\
							unsigned long long mantissa)
{
	size_t		index;

	index = 0;
	while (mantissa > 0)
	{
		if (index == 0)
		{
			if (ft_numlst_prefix(lstrav, 1) == -1)
				return (-1);
			lstrav = lstrav->prev;
			index = lstrav->mem_size - 1;
		}
		else
			index--;
		lstrav->mem[index] = (mantissa % 10) + '0';
		mantissa /= 10;
	}
	return (1);
}

static int					ft_mantissa_div(t_numlst **lst,\
							unsigned long long mantissa)
{
	size_t		count;

	count = 0;
	mantissa ^= 1;
	while (mantissa != 0)
	{
		mantissa ^= 1;
		mantissa >>= 1;
		count++;
	}
	while (count > 1)
	{
		count--;
		if (ft_lst_math_halve(lst) == -1)
			return (-1);
	}
	return (1);
}

t_numlst					*ft_mantissa_to_numlst(unsigned long long mantissa)
{
	t_numlst	*lst;

	mantissa = ft_llurev(mantissa);
	lst = ft_numlst_dec_init();
	if (lst == NULL)
		return (NULL);
	lst->mem[0] = (mantissa % 10) + '0';
	if (ft_mant_to_lst(lst, mantissa / 10) == -1)
	{
		ft_numlst_del(&lst);
		return (NULL);
	}
	if (ft_mantissa_div(&lst, mantissa) == -1)
	{
		ft_numlst_del(&lst);
		return (NULL);
	}
	return (lst);
}
