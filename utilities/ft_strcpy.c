/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 11:12:58 by aholster       #+#    #+#                */
/*   Updated: 2019/10/04 18:38:21 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_utilities.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	len;

	len = ft_strlen(src);
	ft_memcpy(dst, src, len + 1);
	return (dst);
}
