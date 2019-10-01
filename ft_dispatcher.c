/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dispatcher.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:00:54 by aholster       #+#    #+#                */
/*   Updated: 2019/09/30 20:27:00 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

static int			ft_conversion_exception(\
						const char *const restrict specifier,\
						t_writer *const restrict clipb)
{
	int				zeroflag;
	int				padf;
	const size_t	len = 1; //upgrade DISSSS maybe?

	zeroflag = flagverif('0', clipb->flags);
	if (flagverif('-', clipb->flags) == -1)
	{
		if (zeroflag == 1)
			padf = ft_zero_padder(len, clipb);
		else
			padf = ft_space_padder(len, clipb);
		if (padf == -1 || clipb->self(specifier, len, clipb) == -1)
			return (-1);
	}
	else
	{
		if (clipb->self(specifier, len, clipb) == -1)
			return (-1);
		padf = ft_space_padder(len, clipb);
		if (padf == -1)
			return (-1);
	}
	return (1);
}

static t_formatter	ft_lookup_tbl(const int index)
{
	const t_formatter	dispatch_tbl[128] = {
	['a'] = &ft_lowhexpoint,
	['A'] = &ft_caphexpoint,
	['c'] = &ft_char,
	['d'] = &ft_decimal,
	['e'] = &ft_lowsci,
	['E'] = &ft_capsci,
	['f'] = &ft_lowfltpoint,
//	['F'] = &ft_capfltpoint,
	['g'] = &ft_lowshrthd,
	['G'] = &ft_capshrthd,
	['i'] = &ft_decimal,
	['n'] = &ft_n,
	['o'] = &ft_octal,
	['p'] = &ft_ptraddr,
	['s'] = &ft_str,
	['u'] = &ft_unsigned_dec,
	['x'] = &ft_lowhex,
	['X'] = &ft_caphex,
	};

	return (dispatch_tbl[index]);
}

int					ft_dispatcher(const char *restrict specifier,\
				t_writer *const restrict clipb)
{
	const int		index = *specifier;
	t_formatter		function;

	if (specifier[0] != '\0')
	{
		if (index > 127)
			function = NULL;
		else
			function = ft_lookup_tbl(index);
		if (function == NULL)
		{
			if (ft_conversion_exception(&specifier[0], clipb) == -1)
				return (-1);
		}
		else
		{
			if (function(clipb->args, clipb) == -1)
				return (-1);
		}
	}
	return (1);
}
