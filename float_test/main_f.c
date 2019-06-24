/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_f.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/17 17:01:10 by aholster       #+#    #+#                */
/*   Updated: 2019/06/24 15:18:17 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "./../ft_printf.h"

int	floatwrap(int precision, double num);
int	floatwrapbetter(int precision, double num);
int	floatgrap(int precision, double num);


//char	*ft_itoa_float(double d, int n);

void	printfloat(const int precision, const double num)
{
	dprintf(1, "current precision %d\n", precision);
	if (dprintf(1, "F:\t%.*F\n", precision, num) == -1)
		dprintf(1, "printf returned error\n");
//	if (dprintf(1, "f:\t%.*f\n", precision, num) == -1)
//		dprintf(1, "printf returned error\n");
	dprintf(1, "ourF:\t");
	floatwrap(precision, num);
	dprintf(1, "newF:\t");
//	floatwrapbetter(precision, num);
//	dprintf(1, "marinF:\t%s\n", ft_itoa_float(num, precision));

	if (dprintf(1, "G:\t%.*G\n", precision, num) == -1)
		dprintf(1, "printf returned error\n");
//	if (dprintf(1, "g:\t%.*g\n", precision, num) == -1)
//		dprintf(1, "printf returned error\n");
//	dprintf(1, "ourG:\t");
//	floatgrap(precision, num);
	
	if (dprintf(1, "E:\t%.*E\n", precision, num) == -1)
		dprintf(1, "printf returned error\n");
//	if (dprintf(1, "e:\t%.*e\n", precision, num) == -1)
//		dprintf(1, "printf returned error\n");

	if (dprintf(1, "A:\t%.*A\n", precision, num) == -1)
		dprintf(1, "printf returned error\n");
//	if (dprintf(1, "a:\t%.*a\n", precision, num) == -1)
//		dprintf(1, "printf returned error\n");
		
	dprintf(1, "\n");
}


int		main(void)
{
	double	num;
	int precision;

	printf("%zu, %zu, %zu, %zu\n", sizeof(float), sizeof(double), sizeof(long double), sizeof(long long));
	precision = 10;
	num = 123.8999;
	printfloat(precision, num);

	num = 0.5;
	printfloat(precision, num);
	printfloat(0, num);

	num = 0.51;
	printfloat(precision, num);
	printfloat(0, num);

	num = 1.5;
	printfloat(precision, num);
	printfloat(0, num);

	num = 2.5;
	printfloat(10, num);
	printfloat(0, num);

	num = 2.51;
	printfloat(10, num);
	printfloat(0, num);

	num = 2.125;
	printfloat(10, num);
	printfloat(2, num);

	num = 2.126;
	printfloat(10, num);
	printfloat(2, num);

	num = 2.1250009;
	printfloat(10, num);
	printfloat(2, num);

	num = 0.0 / 0.0;
	printfloat(precision, num);

	num = 134.6;
	printfloat(0, num);

	num = 134.7864232;
	printfloat(10, num);
	printfloat(6, num);
	printfloat(3, num);
	printfloat(0, num);

	num = 1.15;
	printfloat(10, num);
	printfloat(1, num);

	num = 1.17;
	printfloat(10, num);
	printfloat(1, num);

	num = 13412989812323124873.44120738;
	printfloat(precision, num);
	
	// printfloatadv("%'-14.*F\n", -1, num);
	// num = 88888888888.441207380080780079567123;
	// printfloat(32, num);
	// printfloat(8, num);
	// printfloat(0, num);
	// printfloatadv("%.*F\n", precision, num);

	num = 0.0;
	printfloat(0, num);

	num = 190100100100100.0;
	printfloat(0, num);
	
	num = 990100100100100.0;
	printfloat(0, num);

	num = 200900400.500600;
	printfloat(3, num);

	num = 200900400.500600;
	printfloat(2000, num);
	return (0);
}
