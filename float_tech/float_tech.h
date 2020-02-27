/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   float_tech.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/23 14:47:32 by aholster       #+#    #+#                */
/*   Updated: 2020/02/27 15:38:10 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_TECH_H
# define FLOAT_TECH_H

# include "./../incl/ft_utilities.h"

# define LSTBUF_SIZE 8

/*
**	LSTBUF_SIZE DOES NOT SUPPORT THE VALUE OF 3, OR smaller than 1
*/

typedef	struct		s_numlst
{
	char			*mem;
	size_t			mem_size;
	struct s_numlst	*next;
	struct s_numlst	*prev;
}					t_numlst;

int					ft_numlst_to_txt(const t_numlst *lst,
						const unsigned int precision,
						char **str, size_t *asize);

void				ft_numlst_del(t_numlst **alst);
size_t				ft_numlst_fwlen(const t_numlst *dec_lst);
size_t				ft_numlst_bwlen(const t_numlst *dec_lst);
t_numlst			*ft_numlst_newnode(void);
t_numlst			*ft_numlst_dec_init(void);

int					ft_numlst_prefix(t_numlst *dec_lst, unsigned short count);
int					ft_numlst_postfix(t_numlst *dec_lst, unsigned short count);
int					ft_numlst_minsize(t_numlst *source, const t_numlst *target);
int					ft_numlst_inline_copy(const t_numlst *source,
						t_numlst *dst);

t_numlst			*ft_mantissa_to_numlst(unsigned long long mantissa);
int					ft_numlst_up_magni(const t_numlst *source,
						t_numlst *dst,
						unsigned char mag);

int					ft_lst_math_add(t_numlst *source, t_numlst *addition);
int					ft_lst_math_mul(t_numlst **source, const char *multiply);
int					ft_lst_math_halve(t_numlst **source);

#endif
