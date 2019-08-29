/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@stuoent.cooam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 16:17:01 by jesmith        #+#    #+#                */
/*   Updated: 2019/08/29 16:27:12 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

// typedef	union u_convert {
// 	unsigned long long	ll;
// 	double				dbl;
// }			t_convert;

int	main(void)
{
	// char i;

	// i = NULL;

	// ft_printf("|%s|\n", i);
	// printf("|%s|\n", i);
	// // char *i = NULL;

	// ft_printf("|ours: %06.16s|\n", i);
	// printf("|test: %06.16s|\n", i);
	// printf("\n");

	// ft_printf("|ours: %016.6s|\n", i);
	// printf("|test: %016.6s|\n", i);
	// printf("\n");

	// ft_printf("|ours: %016.0s|\n", i);
	// printf("|test: %016.0s|\n", i);
	// printf("\n");

	// ft_printf("|ours: %-8s|\n", i);
	// printf("|test: %-8s|\n", i
	// printf("\n");

	// ft_printf("|ours: %.10s|\n", i);
	// printf("|test: %.10s|\n", i);
	// printf("\n");

	// ft_printf("|ours: %032s|\n", i);
	// printf("|test: %032s|\n", i);
	// printf("\n");
	// unsigned long long i;

	// i = 9223372036854775880LLU;

	// t_convert holder;
	float i;
	i = 123.5;
	// unsigned long long b = 18446744073709551615LLU;
	// holder.dbl = i;

	// printf("%llu, %llu\n", b, (unsigned long long)i);
	// double i = 9.6547998786;
	// ft_printf("|ours: |%f|\n", i);
	// ft_printf("|ours: |%012g|\n", i);
	// printf("|test: |%012g|\n", i);
	// ft_printf("|ours: |%80% ds|\n", i, i);
	// printf("|test: |%80% ds|n");
	// char z = '€';

	// unsigned long long a = 92233720368547;
	// int b = 456;
	// unsigned int c = 321;
	// ft_printf("|ours: %9.0c|\n", z);
	// 	printf("|test: %9.0c|\n", z);z
	// 	printf("\n");

	// ft_printf("|%26.0a| |%26a| |%26.16a| |%26.16a| |%26.16a|\n", i, i, i ,i, i);
	// printf("|%26.0a| |%26a| |%26.16a| |%26.16a| |%26.16a|\n",i, i, i, i ,i);
	// printf("\n");
	// char c = 'B';
	// int i = 224;

	// ft_printf("ours: |\n%-50c0%a|\n", '[', 123);
	// printf("test: |\n%-50c0%a|\n", '[', 123);
	// printf("\n");

	printf("|test: |%a|\n", i);
	ft_printf("|test: |%a|\n", i);

	// ft_printf("|ours: %9.0a|\n", i);
	// printf("|test: %9.0a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %.0a|\n", i);
	// printf("|test: %.0a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %0136.20a|\n", i);
	// printf("|test: %0136.20a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %-36.20a|\n", i);
	// printf("|test: %-36.20a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %016.0a|\n", i);
	// printf("|test: %016.0a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %036.0a|\n", i);
	// printf("|test: %036.0a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %66.15a|\n", i);
	// printf("|test: %66.15a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %-26.15a|\n", i);
	// printf("|test: %-26.15a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %36.90a|\n", i);
	// printf("|test: %36.90a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %-6.15a|\n", i);
	// printf("|test: %-6.15a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %-66a|\n", i);
	// printf("|test: %-66a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %033a|\n", i);
	// printf("|test: %033a|\n", i);
	// printf("\n");


	// ft_printf("|ours: |%.0a|\n", i);
	// printf("|test: |%.0a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#016.65a|\n", i);
	// printf("|test: %#016.65a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#036.20a|\n", i);
	// printf("|test: %#036.20a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#-36.20a|\n", i);
	// printf("|test: %#-36.20a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#016.0a|\n", i);
	// printf("|test: %#016.0a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#36.0a|\n", i);
	// printf("|test: %#36.0a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#36.90a|\n", i);
	// printf("|test: %#36.90a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#066.15a|\n", i);
	// printf("|test: %#066.15a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#-26.15a|\n", i);
	// printf("|test: %#-26.15a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#-6.15a|\n", i);
	// printf("|test: %#-6.15a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#-66a|\n", i);
	// printf("|test: %#-66a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#033a|\n", i);
	// printf("|test: %#033a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#a|\n", i); // wrong output
	// printf("|test: %#a|\n", i);
	// printf("\n");

	// ft_printf("|ours: %#.0a|\n", i);
	// printf("|test: %#.0a|\n", i);
	// printf("\n");
	return (0);
}