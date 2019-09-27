/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_internals.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 18:17:05 by aholster       #+#    #+#                */
/*   Updated: 2019/09/27 18:47:58 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INTERNALS_H
# define FT_INTERNALS_H

# include "./../libft/libft.h"
# include "./../float_tech/float_tech.h"

# include <limits.h>

# define BUFFSIZE	8
# define FUNCSIZE	58

# define MAX_INT	2147483647

# define VALID_FLG "hjzl# *.-+L0123456789"
# define VALID_D_FLG "hl"

/*
**	VALID_FLG and VALID_D_FLG handle what constitutes valid characters in flags
**	double-lettered-flags MUST be valid normal flags
**	to add new conversions, add them into the dispatcher array.
*/

typedef union		u_nptrs
{
	char			*hh;
	short			*h;
	int				*i;
	long			*l;
	long long		*ll;
}					t_nptrs;

struct s_print;

typedef int			(*t_wrt_ptr)(const char *restrict, size_t, \
						struct s_print * const);

typedef	int			(*t_writer)(va_list args, struct s_print * const);

typedef struct		s_print
{
	char			*buffer;
	t_list			**alst;
	size_t			history;
	size_t			current;
	int				fd;
	va_list			origin_args;
	va_list			args;
	t_wrt_ptr		printer;
	struct s_flag	*flags;
}					t_print;

/*
** history should be unsigned long long bc of %lln
*/

typedef	struct		s_flag
{
	unsigned\
	long long		statiflags[2];
	unsigned\
	long long		statidoubles[2];
	unsigned\
	long long		actiflags[2];
	unsigned\
	long long		actidoubles[2];
	unsigned int	precision;
	unsigned int	padding;
}					t_flag;

int					ft_format(const char *restrict format,\
						t_print *const restrict clipb);

int					ft_dispatcher(const char *restrict specifier,\
							t_writer *functbl, t_print *const restrict clipb);
void				ft_flagharvest(const char *restrict format,\
						size_t *const aindex, t_print *const restrict clipb);
void				ft_flinit(t_print *const restrict clipb, t_flag *flags);

void				ft_functblinit(t_writer *functbl);

int					ft_zero_padder(unsigned short len,\
								t_print *const restrict clipb);
int					ft_space_padder(unsigned short len,\
								t_print *const restrict clipb);
int					pad_spaces(size_t amount,\
								t_print *const restrict clipb);
int					pad_zero(size_t amount, t_print *const restrict clipb);

int					ft_float_padder(unsigned short len, unsigned short dec, \
						t_print *const restrict clipb);

void				ft_float_rounder(char *buffer, \
						t_print *const restrict clipb, size_t nb_len);
void				ft_shrthd_rounder(char *buffer, \
						t_print *const restrict clipb, size_t nb_len);

void				ft_hexpoint_rounder(char *buffer, \
						t_print *const restrict clipb, short *expon);

void				ft_sci_rounder(char *buffer, t_print *const restrict clipb, \
						size_t nb_len);
size_t				ft_expon_rounding(char *buffer, size_t nb_len, \
						t_print *const restrict clipb);

unsigned short		ft_lowhexpoint_prec(char *buffer, \
						t_print *const restrict clipb);
int					ft_prefix(int neg, t_print *const restrict clipb);
unsigned short		ft_ull_len(unsigned long long num, int base);
unsigned short		ft_negpos_handler(t_print *const clipb, int neg);

size_t				ft_x_offset(char **buffer, size_t *nb_len, \
						t_print *const restrict clipb, int neg);
int					ft_expon_finder(char *buffer, size_t nb_len);
void				ft_float_exceptions(char *buffer, long double nb, \
						short *expon, t_print *const restrict clipb);
void				ft_expon_len(char *buffer, size_t *new_len, \
						t_print *const restrict clipb, int neg);


int					ft_signconv(va_list args,\
						unsigned long long *const holder,\
						const t_flag *const flags);
void				ft_unsignconv(va_list args,\
						unsigned long long *const holder,\
						const t_flag *const flags);
int					ft_longdouble_conv(va_list args, long double *holder,\
						const t_flag *flags);
int					flagverif(const unsigned char c, const t_flag *flags);
int					doubleverif(const unsigned char c,\
						const t_flag *flags);

int					ft_str(va_list args, t_print *const restrict clipb);
int					ft_ptraddr(va_list args, t_print *const restrict clipb);
int					ft_decimal(va_list args, t_print *const restrict clipb);
int					ft_unsigned_dec(va_list args,\
							t_print *const restrict clipb);
int					ft_char(va_list args, t_print *const restrict clipb);
int					ft_octal(va_list args, t_print *const restrict clipb);
int					ft_lowhex(va_list args, t_print *const restrict clipb);
int					ft_caphex(va_list args, t_print *const restrict clipb);
int					ft_lowsci(va_list args, t_print *const restrict clipb);
int					ft_capsci(va_list args, t_print *const restrict clipb);
int					ft_lowshrthd(va_list args, t_print *const restrict clipb);
int					ft_capshrthd(va_list args, t_print *const restrict clipb);
int					ft_shrthd_print(char *buffer, \
						size_t offset, t_print *const clipb, size_t new_len);
size_t				ft_shrthd_offset(char **buffer, size_t *nb_len, \
						t_print *const restrict clipb, int neg);
int					ft_lowsci_print(char *buffer, \
						size_t nb_len, t_print *const clipb, int expon);
int					ft_capsci_print(char *buffer, \
						size_t nb_len, t_print *const clipb, int expon);
int					ft_lowhexpoint(va_list args,\
							t_print *const restrict clipb);
int					ft_caphexpoint(va_list args,\
							t_print *const restrict clipb);
int					ft_lowfltpoint(va_list args,\
							t_print *const restrict clipb);
int					ft_capfltpoint(va_list args,\
							t_print *const restrict clipb);
int					ft_n(va_list args, t_print *const restrict clipb);

#endif
