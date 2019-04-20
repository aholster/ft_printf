/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:13 by aholster       #+#    #+#                */
/*   Updated: 2019/04/20 14:09:35 by jesmith       ########   odam.nl         */
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
# define DBLFLG "hl"

/*
**	VALFLG and DBLFLG handle what constitutes valid characters in flags
**	doubleflags MUST be valid normal flags
**	to add new conversions, add them into the dispatcher array.
*/

typedef	struct			s_flag //corrected
{
	unsigned long long	standflags[2];
	unsigned long long	doubleflags[2];
	unsigned long long	actiflags[2];
	unsigned long long	actidoubles[2];
	int					precision;
	int					padding;
//	int					npadding;

	t_list				**lst;
	size_t				history;
	int					fd;
//	int					(*print)(char *mem, size_t size, t_flag *flags);
}						t_flag;

int						ft_lstbuffer(va_list ap, char *format,\
						char **out, size_t *len);


void					ft_bufmanager(char *mem, size_t size, t_flag *flags);
int						ft_format(va_list ap, char *format, t_flag *flags);

int						ft_printf(char *format, ...);
int						ft_dispatcher(va_list ap, char *specifier,\
						void *functbl[53], t_flag *flags);
int						ft_flagharvest(unsigned char *format, t_flag *flags);
void					ft_flinit(const int fd, t_flag *flags);

#endif
