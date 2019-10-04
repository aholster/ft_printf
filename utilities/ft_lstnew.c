/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 19:28:30 by aholster       #+#    #+#                */
/*   Updated: 2019/10/04 18:43:00 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (head == NULL)
		return (NULL);
	if (!(content))
	{
		head->content = NULL;
		head->content_size = 0;
	}
	else
	{
		head->content = (void *)malloc(sizeof(void) * content_size);
		if (head->content == NULL)
		{
			free(head);
			return (NULL);
		}
		ft_memcpy(head->content, content, content_size);
		head->content_size = content_size;
	}
	head->next = NULL;
	return (head);
}
