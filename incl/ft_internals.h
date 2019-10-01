/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_internals.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 18:17:05 by aholster       #+#    #+#                */
/*   Updated: 2019/10/01 14:55:42 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INTERNALS_H
# define FT_INTERNALS_H

# include "./../libft/libft.h"
# include "./../float_tech/float_tech.h"
# include "./ft_writer.h"

# include <limits.h>

# define VALID_FLG "hjzl# *.-+L0123456789"
# define VALID_D_FLG "hl"

/*
**	VALID_FLG and VALID_D_FLG handle what constitutes valid characters in flags
**	double-lettered-flags MUST be valid normal flags
**	to add new conversions, add them into the dispatcher array.
*/

typedef union	u_nptrs
{
	char		*hh;
	short		*h;
	int			*i;
	long		*l;
	long long	*ll;
}				t_nptrs;

typedef	struct	s_flag
{
	uint32_t	statiflags[4];
	uint32_t	statidoubles[4];
	uint32_t	actiflags[4];
	uint32_t	actidoubles[4];
	uint		precision;
	uint		padding;
}				t_flag;

typedef	int		(*t_formatter)(va_list args, struct s_writer *const restrict);

/*
** history should be unsigned long long bc of %lln
*/

int				ft_format(const char *restrict format,\
					t_writer *const restrict clipb);

int				ft_dispatcher(const char *restrict specifier,\
					t_writer *const restrict clipb);
void			ft_flagharvest(const char *restrict format,\
					size_t *const aindex, t_writer *const restrict clipb);
void			ft_flinit(t_writer *const restrict clipb,\
					t_flag *const restrict flags);

int				ft_zero_padder(unsigned short len,\
					t_writer *const restrict clipb);
int				ft_space_padder(unsigned short len,\
					t_writer *const restrict clipb);
int				pad_spaces(size_t amount,\
					t_writer *const restrict clipb);
int				pad_zero(size_t amount, t_writer *const restrict clipb);

int				ft_float_padder(unsigned short len,\
					unsigned short dec, t_writer *const restrict clipb);

void			ft_rounder(t_float conversion, char *buffer,\
					t_writer *const restrict clipb, size_t nb_len);

void			ft_shorthand_prec(char *buffer,\
					unsigned short nb_len, t_writer *const restrict clipb);
unsigned short	ft_lowhexpoint_prec(char *buffer,\
					t_writer *const restrict clipb);
int				ft_prefix(int neg, t_writer *const restrict clipb);
unsigned short	ft_ull_len(unsigned long long num, int base);
void			ft_float_exceptions(char *buffer, long double nb,\
					short *expon, t_writer *const restrict clipb);

int				ft_signconv(va_list args,\
					unsigned long long *const holder,\
					const t_flag *const restrict flags);
void			ft_unsignconv(va_list args,\
					unsigned long long *const holder,\
					const t_flag *const restrict flags);
int				ft_longdouble_conv(va_list args, long double *holder,\
					const t_flag *const restrict flags);
int				flagverif(const unsigned char c,\
					const t_flag *const restrict flags);
int				doubleverif(const unsigned char c,\
					const t_flag *const restrict flags);

int				ft_str(va_list args, t_writer *const restrict clipb);
int				ft_ptraddr(va_list args, t_writer *const restrict clipb);
int				ft_decimal(va_list args, t_writer *const restrict clipb);
int				ft_unsigned_dec(va_list args, t_writer *const restrict clipb);
int				ft_char(va_list args, t_writer *const restrict clipb);
int				ft_octal(va_list args, t_writer *const restrict clipb);
int				ft_lowhex(va_list args, t_writer *const restrict clipb);
int				ft_caphex(va_list args, t_writer *const restrict clipb);
int				ft_lowsci(va_list args, t_writer *const restrict clipb);
int				ft_capsci(va_list args, t_writer *const restrict clipb);
int				ft_lowshrthd(va_list args, t_writer *const restrict clipb);
int				ft_capshrthd(va_list args, t_writer *const restrict clipb);
int				ft_lowhexpoint(va_list args,\
					t_writer *const restrict clipb);
int				ft_caphexpoint(va_list args,\
					t_writer *const restrict clipb);
int				ft_lowfltpoint(va_list args,\
					t_writer *const restrict clipb);
int				ft_n(va_list args, t_writer *const restrict clipb);

#endif
