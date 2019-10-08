/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_parser.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/01 18:41:58 by aholster       #+#    #+#                */
/*   Updated: 2019/10/08 21:57:25 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLAG_PARSER_H
# define FT_FLAG_PARSER_H

# include "./../incl/ft_internals.h"

# define VALID_FLG "hjzl# *.-+L0123456789"

typedef void	(*t_flag_handler)(const char *const restrict,\
					size_t *const restrict,\
					t_writer *const restrict);

void			ft_turn_on_flag(const char c, t_flag *const restrict flags);

void			ft_flag_flip(const char *const restrict format,\
					size_t *const restrict aindex,\
					t_writer *const restrict clipb);
void			ft_flag_num_parse(const char *const restrict format,\
					size_t *const restrict aindex,\
					t_writer *const restrict clipb);
void			ft_flag_arg_extract(const char *const restrict format,\
					size_t *const restrict aindex,\
					t_writer *const restrict clipb);
void			ft_flag_precision(const char *const restrict format,\
					size_t *const restrict aindex,\
					t_writer *const restrict clipb);

#endif
