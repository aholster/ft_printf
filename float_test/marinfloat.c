#include "libft.h"

static char		*crazy_things_of_printf_float(int j, char *flo)
{
	char *string;

	if (flo[j] == '.')
		j--;
	if (flo[j] != '9')
		flo[j]++;
	else
	{
		if (j > 0)
		{
			flo[j] = '0';
			flo = crazy_things_of_printf_float(j - 1, flo);
		}
		else
		{
			flo[j] = '0';
			string = ft_strjoin("1", flo);
			free(flo);
			return (string);
		}
	}
	return (flo);
}

static int		ft_make_int(long long i, char **flo, int n)
{
	int		j;
	char	*string;

	j = 0;
	string = ft_itoba(i, 10);
	while (string[j] != '\0')
	{
		flo[0][j] = string[j];
		j++;
	}
	free(string);
	(void)n;
	if (n > 1)
	{
		flo[0][j] = '.';
		j++;
	}
	return (j);
}

char			*ft_itoa_float(double d, int n)
{
	long long	i;
	int			j;
	int			k;
	char		*flo;

	i = (long long)d;
	flo = (char*)ft_memalloc(sizeof(char) * (ft_nbrlen(i, 10) + n + 1));
	j = ft_make_int(i, &flo, n);
	d -= i;
	if (d < 0)
		d *= -1;
	while (j < ((int)ft_nbrlen(i, 10) + n))
	{
		d *= 10.0;
		k = (int)d;
		flo[j] = k + 48;
		d -= (double)k;
		j++;
	}
	if ((int)(d * 10) >= 5)
		flo = crazy_things_of_printf_float(j - 1, flo);
	return (flo);
}
