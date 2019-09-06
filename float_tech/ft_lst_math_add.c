/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_math_add.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/23 19:00:45 by aholster       #+#    #+#                */
/*   Updated: 2019/08/16 16:18:58 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

static int		ft_numlst_addcarry(t_numlst *cur, size_t index)
{
	char	*txt;

	txt = cur->mem;
	while (index > 0)
	{
		index--;
		if (txt[index] == '.')
			continue;
		else if (txt[index] == '9')
			txt[index] = '0';
		else
		{
			txt[index]++;
			return (1);
		}
	}
	if (cur->prev == NULL)
		if (ft_numlst_prefix(cur, 1) == -1)
			return (-1);
	return (ft_numlst_addcarry(cur->prev, cur->prev->mem_size));
}

static int		ft_add_structhandler(t_numlst *addto, t_numlst *addant)
{
	unsigned char	cache;
	size_t			index;

	index = addant->mem_size;
	while (index > 0)
	{
		index--;
		if (addant->mem[index] == '.')
			continue;
		cache = (addant->mem[index] - '0') + (addto->mem[index] - '0');
		if (cache > 9)
		{
			cache -= 10;
			addto->mem[index] = cache + '0';
			if (ft_numlst_addcarry(addto, index) == -1)
				return (-1);
		}
		else
			addto->mem[index] = cache + '0';
	}
	return (1);
}

int				ft_lst_math_add(t_numlst *source, t_numlst *addition)
{
	t_numlst	*srclow;
	t_numlst	*addlow;

	if (ft_numlst_minsize(source, addition) == -1)
		return (-1);
	srclow = source;
	addlow = addition;
	while (addlow->next != NULL)
	{
		addlow = addlow->next;
		srclow = srclow->next;
	}
	while (addlow != NULL)
	{
		if (ft_add_structhandler(srclow, addlow) == -1)
			return (-1);
		srclow = srclow->prev;
		addlow = addlow->prev;
	}
	return (1);
}
