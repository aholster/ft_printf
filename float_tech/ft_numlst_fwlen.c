/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlst_fwlen.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/28 17:49:59 by aholster       #+#    #+#                */
/*   Updated: 2019/08/16 17:37:13 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

size_t			ft_numlst_fwlen(const t_numlst *dec_lst)
{
	size_t			len;
	const t_numlst	*lst;

	len = 0;
	lst = dec_lst;
	while (lst != NULL)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}
