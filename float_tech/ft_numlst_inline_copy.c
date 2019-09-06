/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlst_inline_copy.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/29 14:16:02 by aholster       #+#    #+#                */
/*   Updated: 2019/09/05 11:00:36 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

static int	numlst_copy_backward(const t_numlst *travsrc, t_numlst *travdst)
{
	while (travsrc->prev != NULL)
	{
		if (travdst->prev == NULL)
			if (ft_numlst_prefix(travdst, 1) == -1)
				return (-1);
		travsrc = travsrc->prev;
		travdst = travdst->prev;
		ft_memcpy(travdst->mem, travsrc->mem, travsrc->mem_size);
	}
	while (travdst->prev != NULL)
	{
		travdst = travdst->prev;
		ft_memset(travdst->mem, '0', travdst->mem_size);
	}
	return (1);
}

static int	numlst_copy_forward(const t_numlst *travsrc, t_numlst *travdst)
{
	while (travsrc != NULL)
	{
		ft_memcpy(travdst->mem, travsrc->mem, travsrc->mem_size);
		if (travsrc->next != NULL && travdst->next == NULL)
			if (ft_numlst_postfix(travdst, 1) == -1)
				return (-1);
		travsrc = travsrc->next;
		travdst = travdst->next;
	}
	while (travdst != NULL)
	{
		ft_memset(travdst->mem, '0', travdst->mem_size);
		travdst = travdst->next;
	}
	return (1);
}

int			ft_numlst_inline_copy(const t_numlst *source, t_numlst *dst)
{
	dst->mem[0] = '0';
	dst->mem[1] = '.';
	dst->mem[2] = '0';
	if (numlst_copy_backward(source, dst) == -1)
		return (-1);
	if (numlst_copy_forward(source, dst) == -1)
		return (-1);
	return (1);
}
