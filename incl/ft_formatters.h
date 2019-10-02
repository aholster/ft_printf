/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_formatters.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/01 18:55:03 by aholster       #+#    #+#                */
/*   Updated: 2019/10/02 19:25:01 by aholster      ########   odam.nl         */
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

#endif
