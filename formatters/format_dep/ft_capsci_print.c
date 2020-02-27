/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_capsci_print.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/25 11:19:27 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 08:15:29 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incl/ft_formatters.h"

static size_t		ft_expon_prefix(char *buffer, short expon)
{
	size_t index;

	index = 2;
	buffer[0] = 'E';
	if (expon < 0)
		buffer[1] = '-';
	else
		buffer[1] = '+';
	if (expon < 0)
		expon *= -1;
	if (expon == 0)
	{
		buffer[index] = '0';
		index++;
	}
	if (expon < 10)
	{
		buffer[index] = '0';
		index++;
	}
	return (index);
}

static void			ft_expon_to_buf(short expon, t_writer *const clipb)
{
	char	buffer[10];
	size_t	index;

	index = ft_expon_prefix(buffer, expon);
	if (expon < 0)
		expon *= -1;
	while (expon > 0)
	{
		buffer[index] = expon % 10 + '0';
		index++;
		expon /= 10;
	}
	ft_write_wrap(buffer, index, clipb);
}

static size_t		ft_offset(char *buffer,\
						size_t *nb_len,\
						t_writer *const clipb)
{
	t_flag *const	flags = clipb->flags;
	size_t			offset;

	offset = 0;
	if (buffer[0] == 'X')
	{
		if (flg_verif('+', flags) == 1)
			buffer[0] = '+';
		else if (flg_verif(' ', flags) == 1 && flg_verif('+', flags) == -1)
			buffer[0] = ' ';
		else if (flg_verif('+', flags) == -1 && flg_verif(' ', flags) == -1)
			offset++;
	}
	else if (buffer[0] == '-')
		buffer[0] = '-';
	*nb_len -= offset;
	return (offset);
}

int					ft_capsci_print(char *buffer,\
						size_t nb_len,\
						t_writer *const clipb,\
						short expon)
{
	t_flag *const	flags = clipb->flags;
	size_t			len_extension;
	size_t const	offset = ft_offset(buffer, &nb_len, clipb);

	if (offset == 1 && buffer[nb_len] == '.')
		nb_len--;
	len_extension = ft_nbrlen((long long)expon, 10) + nb_len + 2;
	if (expon < 10 && expon >= 0)
		len_extension++;
	if (flg_verif('-', flags) == -1 && flg_verif('0', flags) == -1)
	{
		ft_space_padder(len_extension, clipb);
	}
	if (flg_verif('-', flags) == -1 && flg_verif('0', flags) == 1)
	{
		ft_zero_padder(len_extension, clipb);
	}
	ft_write_wrap(buffer + offset, nb_len, clipb);
	ft_expon_to_buf(expon, clipb);
	if (flg_verif('-', flags) == 1 && flags->padding > nb_len)
	{
		ft_space_padder(len_extension, clipb);
	}
	return (0);
}
