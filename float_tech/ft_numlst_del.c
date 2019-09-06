/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlst_del.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/26 21:34:18 by aholster       #+#    #+#                */
/*   Updated: 2019/08/28 19:40:19 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

static void	ft_numlst_del_bw(t_numlst *lst)
{
	t_numlst	*trail;

	while (lst != NULL)
	{
		trail = lst;
		lst = lst->prev;
		free(trail->mem);
		trail->mem = NULL;
		trail->mem_size = 0;
		free(trail);
	}
}

void		ft_numlst_del(t_numlst **alst)
{
	t_numlst	*trail;
	t_numlst	*iterator;

	if (alst != NULL)
	{
		ft_numlst_del_bw((*alst)->prev);
		iterator = *alst;
		while (iterator != NULL)
		{
			trail = iterator;
			iterator = iterator->next;
			free(trail->mem);
			trail->mem = NULL;
			trail->mem_size = 0;
			free(trail);
		}
		*alst = NULL;
	}
}
