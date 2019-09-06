/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlst_bwlen.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/01 19:50:20 by aholster       #+#    #+#                */
/*   Updated: 2019/08/16 17:37:21 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

size_t			ft_numlst_bwlen(const t_numlst *dec_lst)
{
	size_t			len;
	const t_numlst	*lst;

	len = 0;
	lst = dec_lst;
	while (lst != NULL)
	{
		lst = lst->prev;
		len++;
	}
	return (len);
}
