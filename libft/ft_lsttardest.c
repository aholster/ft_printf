/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lsttardest.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 16:09:18 by aholster       #+#    #+#                */
/*   Updated: 2019/04/03 18:24:48 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lsttardest(t_list **lst, t_list **target,\
		void (*del)(void *, size_t))
{
	t_list	*trail;
	t_list	*hunter;

	if (target == NULL || *target == NULL || del == NULL)
		return ;
	hunter = *lst;
	if (hunter == *target)
	{
		*lst = hunter->next;
		ft_lstdelone(&hunter, del);
	}
	while (hunter != NULL)
	{
		trail = hunter;
		hunter = hunter->next;
		if (hunter == *target)
		{
			trail->next = hunter->next;
			ft_lstdelone(target, del);
			return ;
		}
	}
}
