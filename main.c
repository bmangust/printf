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


int main(void)
{
    // printf("%d", 1);
    ft_printf("%c %s world No%d --- %c\n", 'r', "hi", 4, 'v');
    // ft_putchar(97);
	// print_sum(5, 1,2,3,4,5);
    return (0);
}

