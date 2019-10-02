/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_internals.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 18:17:05 by aholster       #+#    #+#                */
/*   Updated: 2019/10/02 23:10:00 by aholster      ########   odam.nl         */
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
int				ft_zero_padder(const unsigned short len,\
					t_writer *const restrict clipb);
int				ft_space_padder(const unsigned short len,\
					t_writer *const restrict clipb);
int				pad_spaces(size_t amount, t_writer *const restrict clipb);
int				pad_zero(size_t amount, t_writer *const restrict clipb);

int				flagverif(const unsigned char c,\
					const t_flag *const restrict flags);
int				doubleverif(const unsigned char c,\
					const t_flag *const restrict flags);

#endif
