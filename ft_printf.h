/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:13 by aholster       #+#    #+#                */
/*   Updated: 2019/05/30 19:25:41 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "./libft/libft.h"

# include <stdlib.h>
//	include also in libft.h

# define BUFFSIZE	10
# define FUNCSIZE	58

# define VALFLG "hjlz# *.-+L0123456789"
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
	size_t				current;
	int					fd;
	int					(*printer)(const unsigned char*, size_t, struct s_print*);
	struct s_flag		*flags;
}						t_print;

/*
** history should be unsigned long long bc of %lln
*/

typedef	int				(*t_writer)(va_list, t_print*);

/*
**	change va_list to pointer to circumvent norminette error
*/

typedef	struct			s_flag
{
	unsigned long long	statiflags[2];
	unsigned long long	statidoubles[2];
	unsigned long long	actiflags[2];
	unsigned long long	actidoubles[2];
	unsigned int		precision;
	unsigned int		padding;
}						t_flag;

int						ft_format(va_list ap, unsigned char *format,\
						t_print *clipb);

int						ft_printf(char *format, ...);

int						ft_dispatcher(va_list ap, unsigned char *specifier,\
						t_writer *functbl, t_print *clipb);
size_t					ft_flagharvest(unsigned char *format, t_print *clipb);
void					ft_flinit(t_print *clipb, t_flag *flags);
int						ft_clinit(t_list **lst, int fd, int \
						(*printer)(const unsigned char*, size_t, t_print*),\
							t_print *clipb);
void					ft_functblinit(t_writer *functbl);

int						pad_spaces(size_t amount, t_print *clipb);
int						pad_zero(size_t amount, t_print *clipb);

int						ft_str(va_list ap, t_print *clipb);
int						ft_ptraddr(va_list ap, t_print *clipb);
int						ft_decimal(va_list ap, t_print *clipb);
int						ft_unsigned_dec(va_list ap, t_print	*clipb);

#endif
