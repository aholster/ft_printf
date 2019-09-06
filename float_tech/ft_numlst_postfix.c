/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlst_postfix.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/28 17:59:50 by aholster       #+#    #+#                */
/*   Updated: 2019/08/12 11:10:25 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

int		ft_numlst_postfix(t_numlst *dec_lst, unsigned short count)
{
	unsigned short	added;
	t_numlst		*new;

	added = 0;
	while (dec_lst->next != NULL)
		dec_lst = dec_lst->next;
	while (added < count)
	{
		new = ft_numlst_newnode();
		if (new == NULL)
			return (-1);
		dec_lst->next = new;
		new->prev = dec_lst;
		dec_lst = new;
		added++;
	}
	return (1);
}
