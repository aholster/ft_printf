/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_internals.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 18:17:05 by aholster       #+#    #+#                */
/*   Updated: 2020/02/25 18:19:32 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INTERNALS_H
# define FT_INTERNALS_H

# include "./../incl/ft_utilities.h"
# include "./ft_writer.h"

# include <sys/types.h>

/*
**	VALID_FLG and VALID_D_FLG handle what constitutes valid characters in flags
**	double-lettered-flags MUST be valid normal flags
**	to add new conversions, add them into the dispatcher array.
*/

# define FLG_UNS	8

typedef	struct	s_flag
{
	uint8_t		actiflags[16];
	uint8_t		actidoubles[16];
	uint		precision;
	uint		padding;
}				t_flag;

typedef	int		(*t_formatter)(va_list args, struct s_writer *const);

/*
** history should be unsigned long long bc of %lln
*/

void			ft_format(const char *format,
					t_writer *const clipb);
int				ft_write_wrap(const char *const format,
					const size_t len,
					struct s_writer *const clipb);

void			ft_dispatcher(const char specifier,
					t_writer *const clipb);

void			ft_flagharvest(const char *format,
					size_t *const aindex,
					t_writer *const clipb);

int				flg_verif(const unsigned char c,
					const t_flag *const flags);

int				flgdbl_verif(const unsigned char c,
					const t_flag *const flags);

void			ft_float_padder(unsigned short len,
					const unsigned short dec,
					t_writer *const clipb);
void			ft_zero_padder(const unsigned short len,
					t_writer *const clipb);
void			ft_space_padder(const unsigned short len,
					t_writer *const clipb);
void			pad_spaces(size_t amount, t_writer *const clipb);
void			pad_zero(size_t amount, t_writer *const clipb);

#endif
