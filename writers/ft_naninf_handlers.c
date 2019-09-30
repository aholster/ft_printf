/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_naninf_handlers.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/30 11:23:32 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/30 12:16:11 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

void	ft_captolow(char *buffer)
{
	size_t index;

	index = 0;
	while (index < 3)
	{
		buffer[index] = buffer[index] - 32;
		index++;
	}
}

int		ft_naninf_padding(char *buffer, t_print *const clipb, \
	size_t nb_len)
{
	size_t hold_len;

	hold_len = nb_len;
	if (clipb->flags->padding > 0 && clipb->flags->padding > nb_len)
		nb_len = clipb->flags->padding - nb_len;
	if (flagverif('-', clipb->flags) == -1 && \
	clipb->flags->padding != 0)
		if (pad_spaces(nb_len, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, hold_len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1)
		if (pad_spaces(nb_len, clipb) == -1)
			return (-1);
	return (1);
}
