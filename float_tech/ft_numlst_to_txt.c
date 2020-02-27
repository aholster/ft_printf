/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlst_to_txt.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/26 21:33:22 by aholster       #+#    #+#                */
/*   Updated: 2020/02/27 14:47:19 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "float_tech.h"

static size_t	leng_calc(const t_numlst *lst, const unsigned prec)
{
	size_t			leng;
	size_t			from_dec;

	leng = 0;
	while (lst->mem_size != 3)
	{
		leng += lst->mem_size;
		lst = lst->next;
	}
	leng += 3;
	lst = lst->next;
	from_dec = 0;
	while (lst != NULL && from_dec < prec)
	{
		if (from_dec + lst->mem_size > prec)
			from_dec += prec - from_dec;
		else
			from_dec += lst->mem_size;
		lst = lst->next;
	}
	leng += from_dec;
	if (from_dec < prec)
		leng += prec - from_dec;
	return (leng);
}

static size_t	copy_into_str(char *mem, const t_numlst *lst,\
							const size_t index, const size_t size)
{
	size_t			len;

	ft_memcpy(mem, (lst->mem) + index, lst->mem_size - index);
	len = lst->mem_size - index;
	lst = lst->next;
	while (lst != NULL && len < size)
	{
		if (size - len < lst->mem_size)
		{
			ft_memcpy(mem + len, lst->mem, size - len);
			len += size - len;
			break ;
		}
		ft_memcpy(mem + len, lst->mem, lst->mem_size);
		len += lst->mem_size;
		lst = lst->next;
	}
	if (len < size)
	{
		ft_memset(mem + len, '0', size - len);
		len += size - len;
	}
	return (len);
}

int				ft_numlst_to_txt(const t_numlst *lst,\
				const unsigned int precision, char **amem, size_t *asize)
{
	size_t			index;
	size_t			leng;

	while (lst->prev != NULL)
		lst = lst->prev;
	index = 0;
	while (lst->mem_size != 3 && lst->mem[index] == '0')
	{
		index++;
		if (lst->mem[index] == '\0')
		{
			index = 0;
			lst = lst->next;
		}
	}
	leng = leng_calc(lst, precision) - index;
	*amem = (char *)malloc(sizeof(char) * leng + 10);
	if (*amem == NULL)
		return (-1);
	(*amem)[0] = 'X';
	*asize = copy_into_str(*amem + 1, lst, index, leng) + 1;
	return (1);
}
