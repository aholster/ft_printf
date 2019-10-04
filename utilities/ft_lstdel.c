/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/22 17:40:24 by aholster       #+#    #+#                */
/*   Updated: 2019/10/04 21:37:24 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

static void		ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}

void			ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*holder;
	t_list	*current;

	if (alst == NULL || *alst == NULL || del == NULL)
		return ;
	current = *alst;
	while (current != NULL)
	{
		holder = current->next;
		ft_lstdelone(&current, del);
		free(current);
		current = holder;
	}
	*alst = NULL;
}
