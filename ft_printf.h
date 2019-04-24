/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:13 by aholster       #+#    #+#                */
/*   Updated: 2019/04/24 15:44:50 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

# include <stdlib.h>
//	include also in libft.h

# define BUFFSIZE	10
# define FUNCSIZE	53

# define VALFLG "hijlz# *.-+L0123456789"
# define DBLFLG "hl"

/*
**	VALFLG and DBLFLG handle what constitutes valid characters in flags
**	double-lettered-flags MUST be valid normal flags
**	to add new conversions, add them into the dispatcher array.
*/

typedef struct			s_print
{
	char				*buffer;
	t_list				**alst;
	size_t				history;
	// history should be unsigned long long bc of %lln
	int					fd;
	int					(*printer)(char*, size_t, struct s_print*);
	struct s_flag		*flags;
}						t_print;

typedef	struct			s_flag
{
	unsigned long long	statiflags[2];
	unsigned long long	statidoubles[2];
	unsigned long long	actiflags[2];
	unsigned long long	actidoubles[2];
	int					precision;
	int					padding;
//	int					npadding;
}						t_flag;

int						ft_format(va_list ap, unsigned char *format, t_print *clipb);

int						ft_printf(char *format, ...);
int						ft_dispatcher(va_list ap, char *specifier,\
						void **functbl, t_print *clipb);
int						ft_flagharvest(unsigned char *format, t_print *clipb);
void					ft_flinit(t_print *clipb, t_flag *flags);
int						ft_clinit(t_list **lst, int fd, int \
						(*printer)(char*, size_t, t_print*), t_print *clipb);

#endif
