/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flagharvest.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 17:22:09 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 10:29:47 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_flag_parser.h"

static void				init_flags(char *const f_stock)
{
	ushort	index;
	short	flip;

	index = 0;
	while (VALID_FLG[index] != '\0')
	{
		flip = VALID_FLG[index] / FLG_UNS;
		f_stock[flip] |= (1LLU << (VALID_FLG[index] - (FLG_UNS * flip)));
		index++;
	}
}

static int				valiflag(const char c,\
							const char *const f_stock)
{
	const unsigned short	flip = c / FLG_UNS;

	if (c > 0)
	{
		if ((1LLU << (c - (flip * FLG_UNS)) & f_stock[flip]) > 0)
			return (1);
	}
	return (-1);
}

static t_flag_handler	lookup_tbl(const unsigned char index)
{
	static const t_flag_handler	flag_table[128] = {
		['h'] = &ft_flag_flip,
		['l'] = &ft_flag_flip,
		['*'] = &ft_flag_arg_extract,
		['.'] = &ft_flag_precision,
		['1'] = &ft_flag_num_parse,
		['2'] = &ft_flag_num_parse,
		['3'] = &ft_flag_num_parse,
		['4'] = &ft_flag_num_parse,
		['5'] = &ft_flag_num_parse,
		['6'] = &ft_flag_num_parse,
		['7'] = &ft_flag_num_parse,
		['8'] = &ft_flag_num_parse,
		['9'] = &ft_flag_num_parse,
	};

	return (flag_table[index]);
}

void					ft_flagharvest(const char *format,\
							size_t *const aindex,\
							t_writer *const clipb)
{
	size_t			subdex;
	static char		flg_stock[16] = {'a'};
	t_flag *const	flags = clipb->flags;
	t_flag_handler	submodule;

	if (flg_stock[0] == 'a')
		init_flags(flg_stock);
	subdex = *aindex;
	ft_bzero(flags, sizeof(t_flag));
	while (valiflag(format[subdex], flg_stock) > 0)
	{
		submodule = lookup_tbl(format[subdex]);
		if (submodule != NULL)
		{
			submodule(format, &subdex, clipb);
		}
		else
		{
			ft_turn_on_flag(format[subdex], flags);
			subdex++;
		}
	}
	*aindex = subdex;
}
