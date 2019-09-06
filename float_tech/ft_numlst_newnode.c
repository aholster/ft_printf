/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlst_newnode.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/27 18:24:47 by aholster       #+#    #+#                */
/*   Updated: 2019/08/12 11:03:21 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

t_numlst	*ft_numlst_newnode(void)
{
	t_numlst	*node;

	node = (t_numlst *)malloc(sizeof(t_numlst));
	if (node == NULL)
		return (NULL);
	node->mem = (char *)malloc(sizeof(char) * LSTBUF_SIZE);
	if (node->mem == NULL)
	{
		free(node);
		return (NULL);
	}
	ft_memset(node->mem, '0', LSTBUF_SIZE);
	node->mem_size = LSTBUF_SIZE;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
