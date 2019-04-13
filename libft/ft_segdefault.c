/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_segdefault.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 17:57:56 by aholster       #+#    #+#                */
/*   Updated: 2019/03/27 16:20:40 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_segdefault(void)
{
	size_t	index;
	char	*str;

	index = 0;
	str = NULL;
	ft_putendl("\e[0;31mWARNING: this is an intentional segfault caused \
by segdefualt");
	ft_putstr("Inevitably many shall fault the hands of those who felled");
	ft_putstr(" <this code>, but segdefualt merely performs the duty of its");
	ft_putendl(" office, to further fear it is redundant.");
	ft_putstr("those more sensible would place responsibility with those who");
	ft_putendl(" forced the hands of segdefualt.");
	ft_putendl("\e[0;33mMay imperial justice account in all balance.\e[0;00m");
	while (str[index] != '\0')
	{
		index++;
	}
}
