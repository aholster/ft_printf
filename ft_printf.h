/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:13 by aholster       #+#    #+#                */
/*   Updated: 2019/09/18 18:20:08 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int					ft_printf(const char *restrict format, ...);
int					ft_vprintf(const char *restrict format, va_list args);

int					ft_asprintf(char **ret, const char *restrict format, ...);
int					ft_vasprintf(char **ret, const char *restrict format,\
						va_list args);

int					ft_dprintf(const int fd, const char *restrict format, ...);
int					ft_vdprintf(const int fd, const char *restrict format,\
						va_list args);

// int				ft_sprintf(char *str, const char *restrict format, ...);
// int				ft_vsprintf(char *str, const char *restrict format, va_list arg);

// int				ft_snprintf(char *str, size_t size,\
// 					const char *restrict format, ...);
// int				ft_vsnprintf(char *str, size_t size,\
// 					const char *restrict format, va_list args);
#endif
