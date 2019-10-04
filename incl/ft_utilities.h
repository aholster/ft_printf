/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utilities.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/04 17:41:23 by aholster       #+#    #+#                */
/*   Updated: 2019/10/04 19:08:48 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILITIES_H
# define FT_UTILITIES_H

# include <stddef.h>
# include <stdlib.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_bzero(void *restrict s, size_t n);
void				*ft_memcpy(void *const restrict dst,\
						const void *const restrict src,\
						const size_t n);
void				*ft_memmove(void *dst, void const *src, size_t len);
void				*ft_memset(void *restrict b,\
						const int c,\
						const size_t len);
void				*ft_memdup(const void *const restrict src,\
						const size_t len);
int					ft_memcmp(void const *s1, void const *s2, size_t n);

char				*ft_strcpy(char *dst, const char *src);

size_t				ft_strlen(char const *s);
int					ft_islowercase(int c);

unsigned int		ft_nbrlen(long long n, unsigned int base);

void				ft_del(void *data, size_t size);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstaddend(t_list **lst, t_list *new);
int					ft_lstmemtomem(char **feed,\
						size_t *totallen,\
						t_list *lst);

#endif
