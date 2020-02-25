/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flt_support.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/04 18:57:11 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 13:18:43 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLT_SUPPORT_H
# define FT_FLT_SUPPORT_H

# include <stddef.h>

typedef union		u_float
{
	long double		ld;
	unsigned short	byte[5];
	unsigned\
	long long		llu;
}					t_float;

int					ft_custom_ld_to_text(const long double input,
						const unsigned int precision,
						char **const amem,
						size_t *asize);

#endif
