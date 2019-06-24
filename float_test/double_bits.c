/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   double_bits.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/20 14:00:12 by aholster       #+#    #+#                */
/*   Updated: 2019/06/20 18:38:41 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

typedef union			u_float
{
	double					d;
	unsigned long long		ll;
}						t_float;

static void	biterate(void *mem, size_t size)
{
	size_t	index;
	unsigned char	subdex;
	unsigned char	byte;

	index = size;
	while (index != 0)
	{
		index--;
		subdex = 0;
		byte = ((unsigned char *)mem)[index];
		while (subdex != 0)
		{
			if ((byte & 128) > 0)
				write(1, "1", 1);
			else
				write(1, "0", 1);
			byte = byte << 1;
			subdex++;
		}
//		write(1, " ", 1);
	}
}

void	print_double_bits(double num)
{
	t_float	holder;
	size_t	bidex;

	holder.d = num;
	if ((holder.ll >> 63 & 1) == 1)
		printf("this float is probably negative\n");
	else
		printf("this float is probably positive\n");
	bidex = 0;
	if ((holder.ll >> (63 - bidex) & 1) == 1)
		printf("1 ");
	else
		printf("0 ");
	bidex++;
	while (bidex < 12)
	{
		if ((holder.ll >> (63 - bidex) & 1) == 1)
			printf("1");
		else
			printf("0");
		bidex++;
	}
	printf(" ");
	while (bidex < 64)
	{
		if ((holder.ll >> (63 - bidex) & 1) == 1)
			printf("1");
		else
			printf("0");
		bidex++;
	}
}

void	bitwrapper(double num)
{
	printf("current float with prec 20:|%.20F|\n", num);
	print_double_bits(num);
	printf("\n");
	biterate(&num, 8);
	printf("\n");
}

int	main(void)
{
	bitwrapper(1.0);
	bitwrapper(-1.0);
	bitwrapper(5.0);
	bitwrapper(-5.0);
	bitwrapper(0.5);
	bitwrapper(-0.5);
	bitwrapper(1.5);
	bitwrapper(-1.5);
	bitwrapper(20.0);
	bitwrapper(8.0);
	bitwrapper(22.0);
	return (0);
}
