/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_parser.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/01 18:41:58 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 13:18:55 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLAG_PARSER_H
# define FT_FLAG_PARSER_H

# include "./../incl/ft_internals.h"

# define VALID_FLG "hjzl# *.-+L0123456789"

typedef void	(*t_flag_handler)(const char *const,
					size_t *const,
					t_writer *const);

void			ft_turn_on_flag(const char c, t_flag *const flags);

void			ft_flag_flip(const char *const format,
					size_t *const aindex,
					t_writer *const clipb);
void			ft_flag_num_parse(const char *const format,
					size_t *const aindex,
					t_writer *const clipb);
void			ft_flag_arg_extract(const char *const format,
					size_t *const aindex,
					t_writer *const clipb);
void			ft_flag_precision(const char *const format,
					size_t *const aindex,
					t_writer *const clipb);

#endif
