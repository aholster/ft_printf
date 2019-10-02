/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expon_handlers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/01 10:52:39 by jesmith        #+#    #+#                */
/*   Updated: 2019/10/02 19:17:21 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static int	ft_nonzero(char *buffer, size_t nb_len)
{
	size_t len;

	len = 1;
	while (len < nb_len)
	{
		if (buffer[len] == '0' || buffer[len] == '.')
			len++;
		else
			break ;
	}
	if (len < nb_len)
		return (1);
	return (0);
}

static int	ft_moveback(char *buffer, size_t nb_len)
{
	int		index;
	size_t	one_dex;

	index = 0;
	while (buffer[index] != '.')
		index++;
	one_dex = index + 1;
	ft_memmove(buffer + index, buffer + one_dex, nb_len);
	ft_memmove(buffer + 3, buffer + 2, nb_len);
	index -= 2;
	return (index);
}

static int	ft_moveforward(char *buffer, size_t nb_len)
{
	int		index;
	size_t	one_dex;

	index = 1;
	while (buffer[index] == '0' || buffer[index] == '.')
		index++;
	one_dex = index + 1;
	ft_memmove(buffer + one_dex, buffer + 3, nb_len);
	ft_memmove(buffer + 1, buffer + index, nb_len);
	index -= 2;
	index *= -1;
	return (index);
}

int			ft_expon_finder(char *buffer, size_t nb_len)
{
	int			index;
	size_t		zero_len;

	index = 0;
	zero_len = ft_nonzero(buffer, nb_len);
	if (buffer[2] == '.' && buffer[1] == '0' && zero_len == 1)
		index = ft_moveforward(buffer, nb_len);
	else if (buffer[2] != '.' && zero_len == 1)
		index = ft_moveback(buffer, nb_len);
	buffer[2] = '.';
	return (index);
}

void		ft_expon_len(char *buffer,\
				size_t *new_len, \
				t_writer *const restrict clipb)
{
	size_t			index;
	size_t			holder;
	unsigned int	precision;

	index = 0;
	precision = clipb->flags->precision;
	while (buffer[index] != '.')
		index++;
	index++;
	if (precision > index)
	{
		holder = precision - index;
		*new_len = index + holder + 1;
	}
	else if (precision == index)
		*new_len = index + 1;
	else if (precision < index && precision != 0)
		*new_len = precision + 1;
	else if (precision == 0 && index != 3)
		*new_len = 8;
}
