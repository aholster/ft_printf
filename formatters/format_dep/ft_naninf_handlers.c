/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_naninf_handlers.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/30 11:23:32 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 10:58:06 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

void	ft_captolow(char *const buffer)
{
	if (ft_islowercase(buffer[0]) == 1)
		buffer[0] = buffer[0] - 32;
	if (ft_islowercase(buffer[1]) == 1)
		buffer[1] = buffer[1] - 32;
	if (ft_islowercase(buffer[2]) == 1)
		buffer[2] = buffer[2] - 32;
}

void	ft_naninf_padding(const char *const buffer,\
			t_writer *const clipb,\
			size_t nb_len,\
			const int is_neg)
{
	const size_t		hold_len = nb_len;
	const t_flag *const	flags = clipb->flags;
	const size_t		padd = flags->padding;

	if (is_neg == -1)
		nb_len++;
	if (padd > 0 && padd > nb_len)
		nb_len = padd - nb_len;
	if (flg_verif('-', flags) == -1 && padd != 0)
	{
		pad_spaces(nb_len, clipb);
	}
	if (is_neg == -1)
	{
		ft_write_wrap("-", 1, clipb);
	}
	ft_write_wrap(buffer, hold_len, clipb);
	if (flg_verif('-', flags) == 1)
	{
		pad_spaces(nb_len, clipb);
	}
}
