#include <stdio.h>

int	main(void)
{
	printf("%2$* 4$*d", 12, 24, 56, 124, 700);
	return (0);
}