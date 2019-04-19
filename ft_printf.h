/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:13 by aholster       #+#    #+#                */
/*   Updated: 2019/04/19 11:36:12 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

# include <stdlib.h>
//	include also in libft.h

# define VALFLG "hijlz# *.-+L0123456789"
# define DBLFLG "lh"

/*
**	VALFLG and DBLFLG handle what constitutes valid characters in flags
**	to add new conversions, add them into the dispatcher array.
*/

typedef struct 			s_statbuf //corrected
{
	char				store[60];
	size_t				cur;
	size_t				history;
}						t_statbuf;

typedef	struct			s_flag //corrected
{
	unsigned long long	standflags[2];
	unsigned int		doubleflags[2];	
	va_list				ap;
	unsigned long long	actiflags[2];	
	int					precision;
	int					spadding;
	int					npadding;
}						t_flag;

int						ft_lstbuffer(va_list ap, char *format,\
						char **out, size_t *len);


void					ft_bufmanager(char input, t_statbuf buffer);
int						ft_formatstat(va_list ap, char *format, size_t *len);

int						ft_printf(char *format, ...);
int						ft_dispatcher(char *specifier, int functbl[53],\
						t_statbuf *buffer, t_flag *flags);
int						ft_flagharvest(char *format, t_flag *flags);
void					ft_flinit(va_list ap, t_flag *flags);

#endif
