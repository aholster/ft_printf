/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_writer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 19:29:47 by aholster       #+#    #+#                */
/*   Updated: 2019/09/18 20:30:01 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WRITER_H
# define FT_WRITER_H

struct s_print;

typedef int			(*t_wrt_ptr)(const char *restrict, size_t,\
						struct s_print *const);

typedef struct		s_print
{
	char			*buffer;
	t_list			**alst;
	size_t			history;
	size_t			current;
	int				fd;
	va_list			args;
	t_wrt_ptr		self;
	struct s_flag	*flags;
}					t_writer;

#endif
