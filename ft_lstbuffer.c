/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstbuffer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/15 18:53:32 by aholster       #+#    #+#                */
/*   Updated: 2019/04/19 11:08:45 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_lstbuffer(va_list ap, char *format, char **out, size_t *len)
{
	t_list *lst;

	if (ft_formatlst(ap, format, &lst) == -1)
		return (-1);

	if (ft_lstmemtomem(out, len, lst) == -1)
		return (-1);
	return (1);
}


int	ft_formatlst(va_list ap, char *format, t_list **lst)
{
	t_list	*cur;
	size_t	index;

	index = 0;
	while (format[index] != '\0')
	{
		
		index++;
	}

}
