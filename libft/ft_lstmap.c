/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/24 13:04:13 by aholster       #+#    #+#                */
/*   Updated: 2019/02/07 20:26:47 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*new;

	head = f(lst);
	lst = lst->next;
	while (lst != NULL)
	{
		new = f(lst);
		if (new == NULL)
			return (NULL);
		ft_lstaddend(&head, new);
		lst = lst->next;
	}
	return (head);
}
