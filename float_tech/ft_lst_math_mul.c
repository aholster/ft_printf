/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_math_mul.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/23 19:00:39 by aholster       #+#    #+#                */
/*   Updated: 2019/09/06 08:11:23 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

static int	ft_mulcarry(t_numlst *cur, size_t index, unsigned char carry)
{
	char	*txt;

	txt = cur->mem;
	while (index > 0)
	{
		index--;
		if (txt[index] == '.')
			continue;
		carry += (txt[index] - '0');
		txt[index] = (carry % 10) + '0';
		carry /= 10;
		if (carry == 0)
			return (1);
	}
	if (cur->prev == NULL)
		if (ft_numlst_prefix(cur, 1) == -1)
			return (-1);
	return (ft_mulcarry(cur->prev, cur->prev->mem_size, carry));
}

static int	ft_mul_structs(t_numlst *nlst, const char mult)
{
	size_t			index;
	size_t			size;
	unsigned char	cache;

	while (nlst->prev != NULL)
		nlst = nlst->prev;
	while (nlst != NULL)
	{
		size = nlst->mem_size;
		index = 0;
		while (index < size)
		{
			if (nlst->mem[index] != '.')
			{
				cache = (nlst->mem[index] - '0') * mult;
				nlst->mem[index] = (cache % 10) + '0';
				if (cache > 9 && ft_mulcarry(nlst, index, cache / 10) == -1)
					return (-1);
			}
			index++;
		}
		nlst = nlst->next;
	}
	return (1);
}

static int	mul_addition_cycler(const t_numlst *source, t_numlst *temp,\
								t_numlst *product, const char *multiply)
{
	unsigned char	mult;
	size_t			index;
	size_t			len;

	index = 0;
	len = ft_strlen(multiply);
	while (index < len)
	{
		mult = multiply[index] - '0';
		if (mult != 0)
		{
			if (len - index == 1 && ft_numlst_inline_copy(source, temp) == -1)
				return (-1);
			else if (len - index != 1 &&\
					ft_numlst_up_magni(source, temp, len - index) == -1)
				return (-1);
			if (mult != 1 && ft_mul_structs(temp, mult) == -1)
				return (-1);
			if (ft_lst_math_add(product, temp) == -1)
				return (-1);
		}
		index++;
	}
	return (1);
}

int			ft_lst_math_mul(t_numlst **source, const char *multiply)
{
	t_numlst		*product;
	t_numlst		*temp;

	product = ft_numlst_dec_init();
	temp = ft_numlst_dec_init();
	if (product == NULL || temp == NULL)
	{
		ft_numlst_del(&product);
		ft_numlst_del(&temp);
		return (-1);
	}
	if (mul_addition_cycler(*source, temp, product, multiply) == -1)
	{
		ft_numlst_del(&temp);
		ft_numlst_del(&product);
		ft_numlst_del(source);
		return (-1);
	}
	ft_numlst_del(&temp);
	ft_numlst_del(source);
	*source = product;
	return (1);
}
