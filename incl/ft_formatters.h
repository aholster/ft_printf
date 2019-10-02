/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_formatters.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/01 18:55:03 by aholster       #+#    #+#                */
/*   Updated: 2019/10/02 21:24:10 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FORMATTERS_H
# define FT_FORMATTERS_H

# include "./ft_internals.h"

typedef union	u_nptrs
{
	char		*hh;
	short		*h;
	int			*i;
	long		*l;
	long long	*ll;
}				t_nptrs;

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
int				ft_lowhexpoint(va_list args, t_writer *const restrict clipb);
int				ft_caphexpoint(va_list args, t_writer *const restrict clipb);
int				ft_lowfltpoint(va_list args, t_writer *const restrict clipb);
int				ft_capfltpoint(va_list args, t_writer *const restrict clipb);
int				ft_n(va_list args, t_writer *const restrict clipb);

/*
**			support functions below this line
*/

int				ft_signconv(va_list args,\
					unsigned long long *const restrict holder,\
					const t_flag *const restrict flags);
void			ft_unsignconv(va_list args,\
					unsigned long long *const restrict holder,\
					const t_flag *const restrict flags);
int				ft_longdouble_conv(va_list args,\
					long double *const restrict holder,\
					const t_flag *const restrict flags);

int				ft_lowsci_print(char *buffer,\
					size_t nb_len,\
					t_writer *const clipb,\
					int expon);

int				ft_capsci_print(char *buffer,\
					size_t nb_len,\
					t_writer *const clipb,\
					int expon);

void			ft_captolow(char *const restrict buffer);
int				ft_naninf_padding(const char *const restrict buffer,\
					t_writer *const restrict clipb,\
					size_t nb_len,\
					const int is_neg);

int				ft_shrthd_print(char *buffer,\
					size_t offset,\
					t_writer *const clipb,\
					size_t new_len);
size_t			ft_shrthd_offset(char *restrict *const restrict buffer,\
					t_writer *const restrict clipb,\
					int is_neg);

void			ft_hexpoint_rounder(char *buffer,\
					t_writer *const restrict clipb,\
					short *expon);

unsigned short	ft_hexpoint_prec(const char *const restrict buffer,\
					t_writer *const clipb,\
					size_t nb_len,\
					short expon);
int				ft_prefix(int is_neg, t_writer *const clipb);
unsigned short	ft_ull_len(unsigned long long num, int base);
unsigned short	ft_reversed(unsigned long long mantissa);
unsigned short	ft_negpos_handler(t_writer *const restrict clipb,\
					int is_neg,\
					short expon);

void			ft_float_rounder(char *buffer,\
					t_writer *const restrict clipb,\
					size_t *nb_len);
void			ft_shrthd_rounder(char *buffer,\
					t_writer *const restrict clipb,\
					size_t *nb_len);

size_t			ft_x_offset(char *restrict *const restrict buffer,\
					size_t *const restrict nb_len,\
					const t_flag *const restrict flags,\
					const int is_neg);
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

unsigned short	ft_lowhexpoint_prec(const char *const restrict buffer,\
					const t_writer *const restrict clipb);
int				ft_prefix(const int is_neg, t_writer *const restrict clipb);
unsigned short	ft_ull_len(unsigned long long num, const int base);

void			ft_rounder(t_float conversion,\
					char *buffer,\
					t_writer *const restrict clipb,\
					size_t nb_len);

#endif
