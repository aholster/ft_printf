/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_math_halve.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/28 20:42:32 by aholster       #+#    #+#                */
/*   Updated: 2019/08/28 16:33:57 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

static int	carryover_division(t_numlst *cur, size_t index, char *txt)
{
	if (cur->mem_size == index + 1)
	{
		if (cur->next == NULL)
			if (ft_numlst_postfix(cur, 1) == -1)
				return (-1);
		cur = cur->next;
		txt = cur->mem;
		index = 0;
	}
	else
		index++;
	if (txt[index] == '.')
		index++;
	txt[index] = txt[index] + 5;
	return (1);
}

static int	struct_halve(t_numlst *trav)
{
	size_t	index;
	char	*txt;

	while (trav != NULL)
	{
		txt = trav->mem;
		index = trav->mem_size;
		while (index != 0)
		{
			index--;
			if (txt[index] == '.' || txt[index] == '0')
				continue ;
			else if (((txt[index] - '0') & 1) == 1)
			{
				txt[index] = ((txt[index] - '1') / 2) + '0';
				if (carryover_division(trav, index, txt) == -1)
					return (-1);
			}
			else
				txt[index] = ((txt[index] - '0') / 2) + '0';
		}
		trav = trav->prev;
	}
	return (1);
}

int			ft_lst_math_halve(t_numlst **source)
{
	t_numlst	*trav;

	trav = *source;
	while (trav->next != NULL)
		trav = trav->next;
	if (struct_halve(trav) == -1)
	{
		ft_numlst_del(source);
		return (-1);
	}
	return (1);
}
