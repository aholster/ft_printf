/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_internals.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 18:17:05 by aholster       #+#    #+#                */
/*   Updated: 2019/10/02 19:24:34 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INTERNALS_H
# define FT_INTERNALS_H

# include "./../libft/libft.h"
# include "./../float_tech/float_tech.h"
# include "./ft_writer.h"

# include <limits.h>
# include <sys/types.h>

# define VALID_FLG "hjzl# *.-+L0123456789"
# define VALID_D_FLG "hl"

/*
**	VALID_FLG and VALID_D_FLG handle what constitutes valid characters in flags
**	double-lettered-flags MUST be valid normal flags
**	to add new conversions, add them into the dispatcher array.
*/

# define FLG_UNS	8

typedef	struct	s_flag
{
	uint8_t		statiflags[16];
	uint8_t		statidoubles[16];
	uint8_t		actiflags[16];
	uint8_t		actidoubles[16];
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

int				ft_float_padder(unsigned short len,\
					const unsigned short dec,\
					t_writer *const restrict clipb);

void			ft_rounder(t_float conversion,\
					char *buffer,\
					t_writer *const restrict clipb,\
					size_t nb_len);

unsigned short	ft_lowhexpoint_prec(const char *const restrict buffer,\
					const t_writer *const restrict clipb);
int				ft_prefix(const int neg, t_writer *const restrict clipb);
unsigned short	ft_ull_len(unsigned long long num, const int base);



size_t			ft_x_offset(char *restrict *const restrict buffer,\
					size_t *const restrict nb_len,\
					const t_flag *const restrict flags,\
					const int neg);
size_t			ft_float_exceptions(char *const restrict buffer,\
					short *const restrict expon,\
					const t_flag *const restrict clipb);

void			ft_sci_rounder(char *buffer,\
						t_writer *const restrict clipb,\
						size_t *nb_len);
size_t			ft_expon_rounding(char *buffer,\
					size_t nb_len,\
					t_writer *const restrict clipb);

int				ft_expon_finder(char *buffer, size_t nb_len);
void			ft_expon_len(char *buffer,\
					size_t *new_len, \
					t_writer *const restrict clipb);

void			ft_float_rounder(char *buffer,\
					t_writer *const restrict clipb,\
					size_t *nb_len);
void			ft_shrthd_rounder(char *buffer,\
					t_writer *const restrict clipb,\
					size_t *nb_len);

unsigned short	ft_hexpoint_prec(const char *const restrict buffer,\
					t_writer *const clipb,\
					size_t nb_len,\
					short expon);
int				ft_prefix(int neg, t_writer *const clipb);
unsigned short	ft_ull_len(unsigned long long num, int base);
unsigned short	ft_reversed(unsigned long long mantissa);
unsigned short	ft_negpos_handler(t_writer *const restrict clipb,\
					int neg,\
					short expon);

void			ft_hexpoint_rounder(char *buffer,\
					t_writer *const restrict clipb,\
					short *expon);

void			ft_captolow(char *const restrict buffer);
int				ft_naninf_padding(const char *const restrict buffer,\
					t_writer *const restrict clipb,\
					size_t nb_len,\
					int neg);

int				ft_capsci_print(char *buffer,\
					size_t nb_len,\
					t_writer *const clipb,\
					int expon);

int				ft_shrthd_print(char *buffer, \
					size_t offset,\
					t_writer *const clipb,\
					size_t new_len);
size_t			ft_shrthd_offset(char *restrict *const restrict buffer,\
					t_writer *const restrict clipb,\
					int neg);

int				ft_lowsci_print(char *buffer,\
					size_t nb_len,\
					t_writer *const clipb,\
					int expon);

int				ft_zero_padder(unsigned short len,\
					t_writer *const restrict clipb);
int				ft_space_padder(unsigned short len,\
					t_writer *const restrict clipb);
int				pad_spaces(size_t amount, t_writer *const restrict clipb);
int				pad_zero(size_t amount, t_writer *const restrict clipb);

int				ft_signconv(va_list args,\
					unsigned long long *const restrict holder,\
					const t_flag *const restrict flags);
void			ft_unsignconv(va_list args,\
					unsigned long long *const restrict holder,\
					const t_flag *const restrict flags);
int				ft_longdouble_conv(va_list args,\
					long double *const restrict holder,\
					const t_flag *const restrict flags);

int				flagverif(const unsigned char c,\
					const t_flag *const restrict flags);
int				doubleverif(const unsigned char c,\
					const t_flag *const restrict flags);

#endif
