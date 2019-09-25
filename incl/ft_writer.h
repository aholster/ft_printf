/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_writer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 19:29:47 by aholster       #+#    #+#                */
/*   Updated: 2019/09/25 14:43:30 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WRITER_H
# define FT_WRITER_H

# define BUFFSIZE	8

struct s_writer;

typedef int			(*t_wrt_ptr)(const char *restrict, size_t,\
						struct s_writer *const restrict);

// typedef struct		s_writer
// {
// 	char			*buffer;
// 	t_list			**alst;
// 	size_t			history;
// 	size_t			current;
// 	int				fd;
// 	va_list			args;
// 	t_wrt_ptr		self;
// 	struct s_flag	*flags;
// }					t_writer;

typedef struct		s_d_write
{
	char			buffer[BUFFSIZE];
	int				fd;
}					t_d_write;

typedef struct		s_as_write
{
	char			buffer[BUFFSIZE];
	t_list			**alst;
}					t_as_write;

typedef struct		s_sn_write
{
	char			*str;
	size_t			capacity;
}					t_sn_write;

typedef union		u_info_s
{
	t_d_write		*d;
	t_as_write		*as;
	t_sn_write		*sn;
}					t_info_s;

typedef struct		s_writer
{
	size_t			history;
	int				current;
	va_list			args;
	t_wrt_ptr		self;
	t_info_s		info;
	struct s_flag	*flags;
}					t_writer;

#endif
