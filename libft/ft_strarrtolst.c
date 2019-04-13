/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strarrtolst.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 21:26:16 by aholster       #+#    #+#                */
/*   Updated: 2019/04/06 15:41:30 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_strarrtolst(char **strarr)
{
	size_t	index;
	t_list	*head;
	t_list	*holder;
	t_list	*new;

	index = 0;
	head = ft_lstnew(strarr[index], ft_strlen(strarr[index]) + 1);
	if (head == NULL)
		return (NULL);
	holder = head;
	index++;
	while (strarr[index] != NULL)
	{
		new = ft_lstnew(strarr[index], ft_strlen(strarr[index]) + 1);
		if (new == NULL)
		{
			ft_lstdel(&head, &ft_del);
			return (NULL);
		}
		holder = ft_lstaddend(&holder, new);
		index++;
	}
	return (head);
}
