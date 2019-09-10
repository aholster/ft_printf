/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:13 by aholster       #+#    #+#                */
/*   Updated: 2019/09/10 18:45:58 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "./libft/libft.h"
# include "./float_tech/float_tech.h"

# include <stdlib.h>
//	include also in libft.h

# define BUFFSIZE	10
# define FUNCSIZE	58

# define VALID_FLG "hjlz# *.-+L0123456789"
# define VALID_D_FLG "hl"

/*
**	VALID_FLG and VALID_D_FLG handle what constitutes valid characters in flags
**	double-lettered-flags MUST be valid normal flags
**	to add new conversions, add them into the dispatcher array.
*/

typedef union			u_nptrs
{
	char				*hh;
	short				*h;
	int					*i;
	long				*l;
	long long			*ll;
}						t_nptrs;

typedef union			u_float
{
	long double			ld;
	unsigned short		byte[5];
	unsigned long long	llu;
}						t_float;

struct s_print;

typedef int				(*t_wrt_ptr)(const unsigned char*, size_t, \
							struct s_print*);

typedef	int				(*t_writer)(va_list args, struct s_print*);

typedef struct			s_print
{
	char				*buffer;
	t_list				**alst;
	size_t				history;
	size_t				current;
	int					fd;
	va_list				origin_args;
	va_list				args;
	t_wrt_ptr			printer;
	struct s_flag		*flags;
}						t_print;

/*
** history should be unsigned long long bc of %lln
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

int						ft_format(unsigned const char *format,\
						t_print *clipb);

int						ft_printf(const char *format, ...);
int						ft_dprintf(const int fd, const char *format, ...);
int						ft_asprintf(char **ret, const char *format, ...);

int						ft_vprintf(const char *format, va_list args);
int						ft_vdprintf(const int fd, const char *format,\
						va_list args);

int						ft_dispatcher(const unsigned char *specifier,\
								t_writer *functbl, t_print *clipb);
size_t					ft_flagharvest(const unsigned char *format,\
						t_print *clipb);
void					ft_flinit(t_print *clipb, t_flag *flags);

void					ft_functblinit(t_writer *functbl);

int						ft_zero_padder(unsigned short len, t_print *clipb);
int						ft_space_padder(unsigned short len, t_print *clipb);
int						pad_spaces(size_t amount, t_print *clipb);
int						pad_zero(size_t amount, t_print *clipb);
int						ft_float_precision(unsigned short len, t_print *clipb);

void					ft_shortprec(unsigned char *buffer,\
						unsigned short nb_len, t_print *clipb);
int						ft_prefix(int neg, t_print *clipb);
unsigned short			ft_ull_len(unsigned long long num, int base);

int						ft_signconv(va_list args,\
						unsigned long long *holder, const t_flag *flags);
int						ft_unsignconv(va_list args,\
						unsigned long long *holder, const t_flag *flags);
int						ft_floatconv(va_list args, long double *holder,\
						const t_flag *flags);
int						flagverif(const unsigned char c, const t_flag *flags);
int						doubleverif(const unsigned char c,\
						const t_flag *flags);

int						ft_str(va_list args, t_print *clipb);
int						ft_ptraddr(va_list args, t_print *clipb);
int						ft_decimal(va_list args, t_print *clipb);
int						ft_unsigned_dec(va_list args, t_print *clipb);
int						ft_char(va_list args, t_print *clipb);
int						ft_octal(va_list args, t_print *clipb);
int						ft_lowhex(va_list args, t_print *clipb);
int						ft_caphex(va_list args, t_print *clipb);
int						ft_lowsci(va_list args, t_print *clipb);
int						ft_capsci(va_list args, t_print *clipb);
int						ft_lowshrthd(va_list args, t_print *clipb);
int						ft_capshrthd(va_list args, t_print *clipb);
int						ft_lowhexpoint(va_list args, t_print *clipb);
int						ft_n(va_list args, t_print *clipb);

#endif
