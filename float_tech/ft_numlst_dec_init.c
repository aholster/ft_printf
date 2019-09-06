/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlst_init.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/12 11:58:30 by aholster       #+#    #+#                */
/*   Updated: 2019/09/06 08:11:27 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

t_numlst				*ft_numlst_dec_init(void)
{
	t_numlst	*node;

	node = (t_numlst *)malloc(sizeof(t_numlst));
	if (node == NULL)
		return (NULL);
	node->mem = (char *)malloc(sizeof(char) * 3);
	if (node->mem == NULL)
	{
		free(node);
		return (NULL);
	}
	node->mem[0] = '0';
	node->mem[1] = '.';
	node->mem[2] = '0';
	node->mem_size = 3;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
