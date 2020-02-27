/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_writer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 19:29:47 by aholster       #+#    #+#                */
/*   Updated: 2020/02/25 17:48:11 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WRITER_H
# define FT_WRITER_H

# include <stdarg.h>
# include <unistd.h>

# define BUFFSIZE	(2)

struct s_writer;

typedef int			(*t_wrt_ptr)(const char *,\
						size_t,\
						struct s_writer *const);

typedef struct		s_d_write
{
	char			buffer[BUFFSIZE];
	int				fd;
}					t_d_write;

typedef struct		s_as_write
{
	char			*str_vect;
	size_t			current_size;
}					t_as_write;

typedef struct		s_sn_write
{
	char			*str;
	size_t			capacity;
}					t_sn_write;

typedef union		u_info_s
{
	t_d_write		d;
	t_as_write		as;
	t_sn_write		sn;
}					t_info_s;

typedef struct		s_writer
{
	size_t			history;
	size_t			current;
	va_list			args;
	t_wrt_ptr		self;
	t_info_s		info;
	int				err;
	struct s_flag	*flags;
}					t_writer;

#endif
