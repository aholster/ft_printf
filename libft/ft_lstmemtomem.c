/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmemtomem.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/06 15:14:09 by aholster       #+#    #+#                */
/*   Updated: 2019/04/06 15:17:50 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstmemtomem(char **feed, size_t *totallen, t_list *lst)
{
	size_t	index;
	size_t	len;
	t_list	*mov;

	mov = lst;
	index = 0;
	len = 0;
	while (mov != NULL)
	{
		len += mov->content_size;
		mov = mov->next;
	}
	*feed = (char *)malloc(sizeof(char) * (len));
	if (*feed == NULL)
		return (-1);
	while (lst != NULL && index < len)
	{
		ft_memcpy(&((*feed)[index]), lst->content, lst->content_size);
		index += lst->content_size;
		lst = lst->next;
	}
	*totallen = len;
	return (1);
}
