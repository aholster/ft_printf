/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlst_prefix.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/28 18:00:02 by aholster       #+#    #+#                */
/*   Updated: 2019/08/16 16:08:20 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

int		ft_numlst_prefix(t_numlst *dec_lst, unsigned short count)
{
	unsigned short	added;
	t_numlst		*new;

	added = 0;
	while (dec_lst->prev != NULL)
		dec_lst = dec_lst->prev;
	while (added < count)
	{
		new = ft_numlst_newnode();
		if (new == NULL)
			return (-1);
		new->next = dec_lst;
		dec_lst->prev = new;
		dec_lst = new;
		added++;
	}
	return (1);
}
