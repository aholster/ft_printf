/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/01 16:56:13 by aholster       #+#    #+#                */
/*   Updated: 2020/02/19 13:14:54 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <sys/types.h>

int	ft_printf(const char *format, ...);
int	ft_vprintf(const char *format, va_list args);

int	ft_asprintf(char **ret, const char *format, ...);
int	ft_vasprintf(char **ret, const char *format, va_list args);

int	ft_dprintf(const int fd, const char *format, ...);
int	ft_vdprintf(const int fd, const char *format, va_list args);

int	ft_sprintf(char *str, const char *format, ...);
int	ft_vsprintf(char *str, const char *format, va_list arg);

int	ft_snprintf(char *str, size_t size, const char *format, ...);
int	ft_vsnprintf(char *str,
				size_t size,
				const char *format,
				va_list args);
#endif
