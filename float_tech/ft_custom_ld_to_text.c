/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_custom_ld_to_text.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/26 17:50:52 by aholster       #+#    #+#                */
/*   Updated: 2019/10/04 18:58:04 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"
#include "./../incl/ft_flt_support.h"

static int	posiponent_loop(t_numlst **alst, short exponent)
{
	const char		*expo_table[5] = {"2", "16", "256", "65536", "268435456"};
	const char		prog_table[5] = {1, 4, 8, 16, 28};
	unsigned char	cur_expo;

	while (exponent > 0)
	{
		if (exponent >= 28)
			cur_expo = 4;
		else if (exponent >= 16)
			cur_expo = 3;
		else if (exponent >= 8)
			cur_expo = 2;
		else if (exponent >= 4)
			cur_expo = 1;
		else
			cur_expo = 0;
		if (ft_lst_math_mul(alst, expo_table[cur_expo]) == -1)
		{
			ft_numlst_del(alst);
			return (-1);
		}
		exponent -= prog_table[cur_expo];
	}
	return (1);
}

static int	exponent_calculation(t_numlst **alst, short exponent)
{
	if (exponent < 0)
		while (exponent != 0)
		{
			if (ft_lst_math_halve(alst) == -1)
			{
				ft_numlst_del(alst);
				return (-1);
			}
			exponent++;
		}
	else
	{
		if (posiponent_loop(alst, exponent) == -1)
			return (-1);
	}
	return (1);
}

static int	exception_catch(t_float num,\
				char **const amem,\
				size_t *asize)
{
	if (!(num.ld == num.ld))
	{
		*amem = (char *)ft_memdup("nan", 3);
		*asize = 3;
	}
	else if ((num.byte[4] & 0x1) == 1)
	{
		*amem = (char *)ft_memdup("inf", 3);
		*asize = 3;
	}
	else
	{
		*amem = (char *)ft_memdup("inf", 3);
		*asize = 3;
	}
	if (*amem == NULL)
		return (-1);
	else
		return (1);
}

int			ft_custom_ld_to_text(const long double input,\
				const unsigned int precision,\
				char **const amem,\
				size_t *asize)
{
	t_float				num;
	short				exponent;
	t_numlst			*lst;

	num.ld = input;
	exponent = (num.byte[4] & 0x7FFF) - 16383;
	if (exponent == 16384)
		return (exception_catch(num, amem, asize));
	else
	{
		lst = ft_mantissa_to_numlst(num.llu);
		if (lst == NULL)
			return (-1);
		if (exponent_calculation(&lst, exponent) == -1)
			return (-1);
		if (ft_numlst_to_txt(lst, precision, &(*amem), asize) == -1)
		{
			ft_numlst_del(&lst);
			return (-1);
		}
		ft_numlst_del(&lst);
	}
	return (1);
}
