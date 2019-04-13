/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 16:07:57 by aholster       #+#    #+#                */
/*   Updated: 2019/01/30 17:14:58 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	index;
	size_t			judex;
	char			*str;

	index = 0;
	while ((s[index] == ' ' || s[index] == '\t' || s[index] == '\n')\
	&& s[index] != '\0')
		index++;
	judex = (ft_strlen(s) - 1);
	while ((s[judex] == ' ' || s[judex] == '\t' || s[judex] == '\n')\
	&& judex >= index)
		judex--;
	str = ft_strsub(s, index, (judex - index) + 1);
	if (str == NULL)
		return (NULL);
	return (str);
}
