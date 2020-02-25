/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dispatcher.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:00:54 by aholster       #+#    #+#                */
/*   Updated: 2020/02/25 10:31:45 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/ft_internals.h"
#include "./incl/ft_formatters.h"

static int			ft_conversion_exception(\
						const char specifier,\
						t_writer *const clipb)
{
	int				zeroflag;
	int				padf;

	zeroflag = flg_verif('0', clipb->flags);
	if (flg_verif('-', clipb->flags) == -1)
	{
		if (zeroflag == 1)
			padf = ft_zero_padder(1, clipb);
		else
			padf = ft_space_padder(1, clipb);
		if (padf == -1 || clipb->self(&specifier, 1, clipb) == -1)
			return (-1);
	}
	else
	{
		if (clipb->self(&specifier, 1, clipb) == -1)
			return (-1);
		padf = ft_space_padder(1, clipb);
		if (padf == -1)
			return (-1);
	}
	return (1);
}

static const t_formatter	g_dispatch_tbl[128] = {
	['a'] = &ft_lowhexpoint,
	['A'] = &ft_caphexpoint,
	['c'] = &ft_char,
	['d'] = &ft_decimal,
	['e'] = &ft_lowsci,
	['E'] = &ft_capsci,
	['f'] = &ft_lowfltpoint,
	['F'] = &ft_capfltpoint,
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

int					ft_dispatcher(const char specifier,\
						t_writer *const clipb)
{
	t_formatter	function;

	if (specifier != '\0')
	{
		if (specifier < 0 || specifier > 127)
			function = NULL;
		else
			function = g_dispatch_tbl[specifier & 0xFF];
		if (function == NULL)
		{
			if (ft_conversion_exception(specifier, clipb) == -1)
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
