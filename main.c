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
	// printf(">%4.3d<\tprintf\n", 42);
	int n;
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
		n = ft_printf("->%+.5d<-\n", 112);
		ft_printf("->12345<-\n");
		ft_printf("printed %d symbols in 1st line\n", n);
	}
	return (0);
}