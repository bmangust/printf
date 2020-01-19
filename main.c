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
		// test = "-12.56891";
		// split = ft_strsplit(test, '.');

		// ft_printf("%s    %s\n", split[0], split[1]);
		// ft_printf("%d\n", ft_atoi(split[0]));
		// ft_printf("%d\n", ft_atoi(split[1]));
		ft_printf("%.6f\n", -0.375);

		
		// test = ft_atoi("12.34568");
		// ft_printf("%d\n", test);
		// //ft_printf("%5.2s is a string", "this");
		//ft_printf("%s %s\n", NULL, "string");
		//ft_printf("%s\n", NULL);
		//ft_printf("%-5c", 42);
		//ft_printf("->%5.2s<-\n", "0123456789");
		// ft_printf("->0123456789<-\n");
		//ft_printf("printed %d symbols in 1st line\n", n);
	}
	return (0);
}