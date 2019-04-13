/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lsttostrarr.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 21:26:14 by aholster       #+#    #+#                */
/*   Updated: 2019/04/06 14:49:51 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lsttostrarr(t_list *lst)
{
	char	**ret;
	size_t	index;

	index = 0;
	ret = (char **)malloc(sizeof(char *) * ft_lstlen(lst) + 1);
	if (ret == NULL)
		return (NULL);
	while (lst != NULL)
	{
		ret[index] = ft_strnew(lst->content_size);
		if (ret[index] == NULL)
		{
			ft_strarrdel(&ret);
			return (NULL);
		}
		ret[index] = ft_memcpy(ret[index], lst->content, lst->content_size);
		index++;
		lst = lst->next;
	}
	ret[index] = NULL;
	return (ret);
}
