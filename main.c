#include "ft_printf.h"
#include "libft.h"

int main(int ac, char **av)
{
	// printf(">%4.3d<\tprintf\n", 42);
	int n, p;
	if (ac == 2)
	{
		ft_printf(av[1], -4);
//		ft_printf("\n");
	}
	else if (ac == 3)
	{
		ft_printf(av[1], ft_atoi(av[2]));
//		ft_printf("\n");
	}
	else if (ac > 3)
	{
		ft_printf(av[1], ft_atoi(av[2]), ft_atoi(av[3]));
//		ft_printf("\n");
	}
	else
	{
		n = ft_printf(">%d<\n", 42);
		p = printf(">%d<\n", 42);
		if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">%d<\n", -42);
        p = printf(">%d<\n", -42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">%5d<\n", -42);
        p = printf(">%5d<\n", -42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">%-5d<\n", -42);
        p = printf(">%-5d<\n", -42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">%-5d<\n", 42);
        p = printf(">%-5d<\n", 42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">%+5d<\n", 42);
        p = printf(">%+5d<\n", 42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">% 5d<\n", 42);
        p = printf(">% 5d<\n", 42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">% -5d<\n", 42);
        p = printf(">% -5d<\n", 42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">% -5d<\n", -42);
        p = printf(">% -5d<\n", -42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">%5.3d<\n", 42);
        p = printf(">%5.3d<\n", 42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">%+5.3d<\n", 42);
        p = printf(">%+5.3d<\n", 42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">%.3d<\n", 42);
        p = printf(">%.3d<\n", 42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">%+.3d<\n", 42);
        p = printf(">%+.3d<\n", 42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">%+.5d<\n", 42);
        p = printf(">%+.5d<\n", 42);
        if (n == p) printf("SUCCESS\n");
        else {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">% -6.4d<\n", 42);
        p = printf(">% -6.4d<\n", 42);
        if (n == p) printf("SUCCESS\n");
        else
        {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
        n = ft_printf(">% -6.4d<\n", -42);
        p = printf(">% -6.4d<\n", -42);
        if (n == p) printf("SUCCESS\n");
        else
        {
            printf("FAIL\n");
            ft_printf("printed %d symbols in 1st line\n", n);
            ft_printf("printed %d symbols in 2st line\n\n", p);
        }
	}
	return (0);
}