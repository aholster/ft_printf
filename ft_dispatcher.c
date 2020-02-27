/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dispatcher.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:00:54 by aholster       #+#    #+#                */
/*   Updated: 2020/02/27 13:54:11 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/ft_internals.h"
#include "./incl/ft_formatters.h"

static void			ft_conversion_exception(\
						const char specifier,\
						t_writer *const clipb)
{
	int				zeroflag;

	zeroflag = flg_verif('0', clipb->flags);
	if (flg_verif('-', clipb->flags) == -1)
	{
		if (zeroflag == 1)
			ft_zero_padder(1, clipb);
		else
			ft_space_padder(1, clipb);
		ft_write_wrap(&specifier, 1, clipb);
	}
	else
	{
		ft_write_wrap(&specifier, 1, clipb);
		ft_space_padder(1, clipb);
	}
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

void				ft_dispatcher(const char specifier,\
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
			ft_conversion_exception(specifier, clipb);
		}
		else
		{
			if (function(clipb->args, clipb))
			{
				clipb->err = 1;
			}
		}
	}
}
