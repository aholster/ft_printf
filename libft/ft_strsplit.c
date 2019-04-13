/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/20 16:41:45 by aholster       #+#    #+#                */
/*   Updated: 2019/02/01 18:58:56 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_wordskip(char const *s, int c)
{
	unsigned int	index;

	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == (char)c)
			return (index);
		index++;
	}
	return (index);
}

static unsigned int	ft_wordcount(char const *s, char c)
{
	size_t			index;
	unsigned int	ret;

	index = 0;
	ret = 0;
	while (s[index] != '\0')
	{
		while (s[index] == c)
			index++;
		while (s[index] != '\0' && s[index] != c)
			index++;
		if ((s[index] == '\0' && s[index - 1] != c) || s[index] != '\0')
			ret++;
	}
	return (ret);
}

static char			**ft_insert(char const *s, char **array, char c,\
unsigned int *judex)
{
	while (s[*judex] == c)
		*judex = *judex + 1;
	if (s[*judex] != '\0')
	{
		array[0] = ft_strsub(s, *judex, ft_wordskip(&s[*judex], c));
		if (array[0] == NULL)
		{
			while (*array != NULL)
			{
				ft_strclr(*array);
				ft_strdel(&*array);
				array++;
			}
			return (NULL);
		}
		*judex = *judex + ft_wordskip(&s[*judex], c);
	}
	return (array);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**ret;
	unsigned int	wordcount;
	unsigned int	index;
	unsigned int	judex;

	index = 0;
	judex = 0;
	wordcount = ft_wordcount(s, c);
	ret = (char**)malloc(sizeof(char*) * (wordcount + 1));
	if (ret == NULL)
		return (NULL);
	while (index < wordcount)
	{
		if (ft_insert(s, &ret[index], c, &judex) == NULL)
		{
			free(ret);
			ret = NULL;
			return (NULL);
		}
		index++;
	}
	ret[index] = (NULL);
	return (ret);
}
