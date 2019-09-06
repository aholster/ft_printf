/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlst_minsize.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/13 17:13:29 by aholster       #+#    #+#                */
/*   Updated: 2019/08/29 14:13:16 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

int		ft_numlst_minsize(t_numlst *source, const t_numlst *target)
{
	size_t	srclen;
	size_t	tarlen;

	srclen = ft_numlst_fwlen(source);
	tarlen = ft_numlst_fwlen(target);
	if (tarlen > srclen)
	{
		if (ft_numlst_postfix(source, tarlen - srclen) == 0)
			return (-1);
		srclen += tarlen - srclen;
	}
	srclen = ft_numlst_bwlen(source);
	tarlen = ft_numlst_bwlen(target);
	if (tarlen > srclen)
	{
		if (ft_numlst_prefix(source, tarlen - srclen) == 0)
			return (-1);
	}
	return (1);
}
