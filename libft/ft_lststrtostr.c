/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lststrtostr.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/06 15:17:01 by aholster       #+#    #+#                */
/*   Updated: 2019/04/06 19:11:06 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lststrtostr(char **feed, t_list *lst)
{
	size_t	index;
	size_t	len;
	t_list	*mov;

	mov = lst;
	index = 0;
	len = 0;
	while (mov != NULL)
	{
		len += mov->content_size - 1;
		mov = mov->next;
	}
	*feed = (char *)malloc(sizeof(char) * (len) + 1);
	if (*feed == NULL)
		return (-1);
	while (lst != NULL && index < len)
	{
		ft_memcpy(&((*feed)[index]), lst->content, lst->content_size - 1);
		index += lst->content_size - 1;
		lst = lst->next;
	}
	(*feed)[index] = '\0';
	return (1);
}
