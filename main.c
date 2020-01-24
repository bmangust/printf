#include "ft_printf.h"
#include "libft.h"

// int ssum(int d, va_list valist)
// {
// 	int sum  = 0;
// 	int n = d;
// 	int i = 0;
// 	n = va_arg(valist, int);
// 	ft_putnbr(n);
// 	ft_putendl("");
// 	while (n || i < 10)
// 	{
// 		sum += n;
// 		n = va_arg(valist, int);
// 		ft_putnbr(n);
// 		ft_putendl("");
// 		++i;
// 	}
// 	return (sum);
// }

// void print_sum(int n, ...)
// {
// 	int sum  = 0;
// 	va_list	valist;
// 	va_start(valist, n);
// 	sum = ssum(n, valist);
// 	ft_putnbr(sum);
// 	va_end(valist);
// 	ft_putendl("");
// 	va_start(valist, n);
// 	sum = ssum(n, valist);
// 	ft_putnbr(sum);
// 	va_end(valist);
// }


int main(int ac, char **av)
{
	double x;

	x = 1234567890.1234567890139;
	if (ac == 2)
	{
		ft_printf(av[1], -4);
		ft_printf("\n");
	}
	else if (ac == 3)
	{
		ft_printf(av[1], ft_atoi(av[2]));
		ft_printf("\n");
	}
	else if (ac > 3)
	{
		ft_printf(av[1], ft_atoi(av[2]), ft_atoi(av[3]));
		ft_printf("\n");
	}
	else
	{
		// Main check //
		ft_printf("p: %.16Lf\n", x);
		printf(	  "l: %.16Lf\n", x);
	
	//  ft_printf("RES: ->%f fdnbjs<-\n", 126);
	// 	printf("LIB: ->%+f<-\n", 126.375);		

	}
	return (0);
}
