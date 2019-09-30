/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_naninf_handlers.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/30 11:23:32 by jesmith        #+#    #+#                */
/*   Updated: 2019/09/30 13:52:31 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"
#include "./../incl/ft_internals.h"

void	ft_captolow(char *buffer)
{
	if (ft_islowercase(buffer[0]) == 1)
		buffer[0] = buffer[0] - 32;
	if (ft_islowercase(buffer[1]) == 1)
		buffer[1] = buffer[1] - 32;
	if (ft_islowercase(buffer[2]) == 1)
		buffer[2] = buffer[2] - 32;
}

int		ft_naninf_padding(char *buffer, t_print *const clipb, \
	size_t nb_len, int neg)
{
	size_t hold_len;

	if (neg == -1)
		nb_len++;
	hold_len = nb_len;
	if (clipb->flags->padding > 0 && clipb->flags->padding > nb_len)
		nb_len = clipb->flags->padding - nb_len;
	if (flagverif('-', clipb->flags) == -1 && \
	clipb->flags->padding != 0)
		if (pad_spaces(nb_len, clipb) == -1)
			return (-1);
	if (neg == -1)
		if (clipb->printer("-", 1, clipb) == -1)
			return (-1);
	if (clipb->printer(buffer, hold_len, clipb) == -1)
		return (-1);
	if (flagverif('-', clipb->flags) == 1)
		if (pad_spaces(nb_len, clipb) == -1)
			return (-1);
	return (1);
}
