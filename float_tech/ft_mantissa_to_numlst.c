/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mantissa_to_numlst.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/28 18:10:51 by aholster       #+#    #+#                */
/*   Updated: 2019/09/12 18:36:31 by aholster      ########   odam.nl         */
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

int							ft_mantissa_write(unsigned long long mantissa,\
							t_numlst *lst, t_numlst **acur_mant_bit)
{
	while (mantissa != 0)
	{
		if ((mantissa & 1) == 1)
		{
			if (ft_lst_math_add(lst, *acur_mant_bit) == -1)
				return (-1);
		}
		if (ft_lst_math_halve(acur_mant_bit) == -1)
		{
			return (-1);
		}
		mantissa >>= 1;
	}
	return (1);
}

t_numlst					*ft_mantissa_to_numlst(unsigned long long mantissa)
{
	t_numlst	*lst;
	t_numlst	*cur_mant_bit;

	mantissa = ft_llurev(mantissa);
	lst = ft_numlst_dec_init();
	cur_mant_bit = ft_numlst_dec_init();
	if (lst == NULL || cur_mant_bit == NULL)
	{
		ft_numlst_del(&lst);
		ft_numlst_del(&cur_mant_bit);
		return (NULL);
	}
	cur_mant_bit->mem[0] = '1';
	if (ft_mantissa_write(mantissa, lst, &cur_mant_bit) == -1)
	{
		ft_numlst_del(&lst);
		ft_numlst_del(&cur_mant_bit);
		return (NULL);
	}
	ft_numlst_del(&cur_mant_bit);
	return (lst);
}
