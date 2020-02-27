/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_formatters.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/01 18:55:03 by aholster       #+#    #+#                */
/*   Updated: 2020/02/27 11:59:23 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FORMATTERS_H
# define FT_FORMATTERS_H

# include "./ft_internals.h"
# include "./ft_flt_support.h"

typedef union	u_nptrs
{
	char		*hh;
	short		*h;
	int			*i;
	long		*l;
	long long	*ll;
}				t_nptrs;

typedef union	u_floatneg
{
	long double	ld;
	uint8_t		byte[10];
}				t_floatneg;

int				ft_str(va_list args, t_writer *const clipb);
int				ft_ptraddr(va_list args, t_writer *const clipb);
int				ft_decimal(va_list args, t_writer *const clipb);
int				ft_unsigned_dec(va_list args, t_writer *const clipb);
int				ft_char(va_list args, t_writer *const clipb);
int				ft_octal(va_list args, t_writer *const clipb);
int				ft_lowhex(va_list args, t_writer *const clipb);
int				ft_caphex(va_list args, t_writer *const clipb);
int				ft_lowsci(va_list args, t_writer *const clipb);
int				ft_capsci(va_list args, t_writer *const clipb);
int				ft_lowshrthd(va_list args, t_writer *const clipb);
int				ft_capshrthd(va_list args, t_writer *const clipb);
int				ft_lowhexpoint(va_list args, t_writer *const clipb);
int				ft_caphexpoint(va_list args, t_writer *const clipb);
int				ft_lowfltpoint(va_list args, t_writer *const clipb);
int				ft_capfltpoint(va_list args, t_writer *const clipb);
int				ft_n(va_list args, t_writer *const clipb);

/*
**			support functions below this line
*/

int				ft_signconv(va_list args,
					unsigned long long *const holder,
					const t_flag *const flags);
void			ft_unsignconv(va_list args,
					unsigned long long *const holder,
					const t_flag *const flags);
int				ft_longdouble_conv(va_list args,
					long double *const holder,
					const t_flag *const flags);

void			ft_lowsci_print(char *buffer,
					size_t nb_len,
					t_writer *const clipb,
					short expon);

int				ft_capsci_print(char *buffer,
					size_t nb_len,
					t_writer *const clipb,
					short expon);

void			ft_captolow(char *const buffer);
void			ft_naninf_padding(const char *const buffer,
					t_writer *const clipb,
					size_t nb_len,
					const int is_neg);

void			ft_shrthd_print(char *buffer,
					size_t offset,
					t_writer *const clipb,
					size_t new_len);
size_t			ft_shrthd_offset(char **const buffer,
					t_writer *const clipb,
					int is_neg);

void			ft_hexpoint_rounder(char *buffer,
					const t_flag *const flags,
					short *expon);

void			ft_float_rounder(char *buffer,
					const t_flag *const flags,
					size_t *nb_len);
void			ft_shrthd_rounder(char *buffer,
					const t_flag *const flags,
					size_t *nb_len);

size_t			ft_x_offset(char **const buffer,
					size_t *const nb_len,
					const t_flag *const flags,
					const int is_neg);
size_t			ft_float_exceptions(char *const buffer,
					short *const expon,
					const t_flag *const clipb);
unsigned short	ft_ull_len(unsigned long long num, const int base);

void			ft_sci_rounder(char *buffer,
					const t_flag *const flags,
					size_t *nb_len);
size_t			ft_expon_rounding(char *buffer,
					size_t nb_len,
					const t_flag *const flags,
					short expon);

int				ft_expon_finder(char *buffer, size_t nb_len);
void			ft_expon_len(char *buffer,
					size_t *new_len,
					t_writer *const clipb);

void			ft_prefix(const int is_neg, t_writer *const clipb);
unsigned short	ft_reversed(unsigned long long mantissa);

void			ft_lowhexpoint_print(t_writer *const clipb,
					short expon,
					unsigned short nb_len,
					unsigned short str_len);
void			ft_caphexpoint_print(t_writer *const clipb,
					short expon,
					unsigned short nb_len,
					unsigned short str_len);

void			ft_rounder(t_float conversion,
					char *buffer,
					t_writer *const clipb,
					size_t nb_len);

#endif
