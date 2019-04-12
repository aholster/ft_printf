/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Conceptizer.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/01 14:48:20 by aholster       #+#    #+#                */
/*   Updated: 2019/04/01 19:19:06 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include <stdarg.h>
# include <stdio.h>

void	ft_stuff(va_list ap)
{
	int				num;

	num = va_arg(ap, int);
	printf("%d\n", num);
}

void	ft_putnbrs(unsigned int count, ...)
{
	va_list ap;
	unsigned int	index;

	index = 0;
	va_start(ap, count);
	while (index < count)
	{
		ft_stuff(ap);
		index++;
	}
	va_end(ap);
}

int	main(void)
{
	int		arr[10] = {0, 1, 22, 333, 4444, 555, 666, 777, 888, 999};

	ft_putnbrs(11, arr[0], arr[1], arr[2], arr[3], arr[4],\
	arr[5], arr[6], arr[7], arr[8], arr[9]);
	return (1);
}