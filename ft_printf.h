/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:13 by aholster       #+#    #+#                */
/*   Updated: 2019/04/19 18:57:30 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

# include <stdlib.h>
//	include also in libft.h

# define BUFFSIZE	10

# define VALFLG "hijlz# *.-+L0123456789"
# define DBLFLG "lh"

/*
**	VALFLG and DBLFLG handle what constitutes valid characters in flags
**	to add new conversions, add them into the dispatcher array.
*/

typedef	struct			s_flag //corrected
{
	unsigned long long	standflags[2];
	unsigned int		doubleflags[2];
	unsigned long long	actiflags[2];
	int					precision;
	int					spadding;
	int					npadding;

	t_list				**lst;
	size_t				history;
	const int			fd;
	int					(*print)(char *mem, size_t size, t_flag *flags);
}						t_flag;

int						ft_lstbuffer(va_list ap, char *format,\
						char **out, size_t *len);


void					ft_bufmanager(char *mem, size_t size, t_flag *flags);
int						ft_format(va_list ap, char *format, t_flag *flags);

int						ft_printf(char *format, ...);
int						ft_dispatcher(va_list ap, char *specifier,\
						void *functbl[53], t_flag *flags);
int						ft_flagharvest(char *format, t_flag *flags);
void					ft_flinit(const int fd, t_flag *flags);

#endif
