/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 21:38:26 by jesmith        #+#    #+#                */
/*   Updated: 2020/02/27 15:06:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_formatters.h"

static void	ft_str_padding(const char *const str,
				const size_t len,\
				t_writer *const clipb)
{
	t_flag *const	flags = clipb->flags;
	const int		zeroflag = flg_verif('0', flags);

	flags->precision = 0;
	if (flg_verif('-', flags) == -1)
	{
		if (zeroflag == 1)
			ft_zero_padder(len, clipb);
		else
			ft_space_padder(len, clipb);
		ft_write_wrap(str, len, clipb);
	}
	else
	{
		ft_write_wrap(str, len, clipb);
		ft_space_padder(len, clipb);
	}
}

/*
**	the -1 return with l flag is becuase widecharacters are not supported.
*/

int			ft_str(va_list args, t_writer *const clipb)
{
	const char		*str;
	t_flag *const	flags = clipb->flags;
	size_t			len;

	if (flg_verif('l', flags) == 1)
	{
		return (-1);
	}
	str = va_arg(args, char*);
	if (str == NULL)
	{
		str = "(null)";
	}
	if (flg_verif('.', flags) == 1)
	{
		len = ft_strnlen(str, flags->precision);
	}
	else
	{
		len = ft_strlen(str);
	}
	ft_str_padding(str, len, clipb);
	return (0);
}
