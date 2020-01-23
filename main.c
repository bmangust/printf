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
//		double d = 10.123456789;
//		ft_printf("dtoa: %s\n", ft_dtoa(d));
//
//		ft_printf("---01---\n");
//		n = ft_printf(">%d<\n", 42);
//		p = printf(">%d<\n", 42);
//		if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---02---\n");
//        n = ft_printf(">%d<\n", -42);
//        p = printf(">%d<\n", -42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---03---\n");
//        n = ft_printf(">%5d<\n", -42);
//        p = printf(">%5d<\n", -42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---04---\n");
//        n = ft_printf(">%-5d<\n", -42);
//        p = printf(">%-5d<\n", -42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---05---\n");
//        n = ft_printf(">%-5d<\n", 42);
//        p = printf(">%-5d<\n", 42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---06---\n");
//        n = ft_printf(">%+5d<\n", 42);
//        p = printf(">%+5d<\n", 42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---07---\n");
//        n = ft_printf(">% 5d<\n", 42);
//        p = printf(">% 5d<\n", 42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---08---\n");
//        n = ft_printf(">% -5d<\n", 42);
//        p = printf(">% -5d<\n", 42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---09---\n");
//        n = ft_printf(">% -5d<\n", -42);
//        p = printf(">% -5d<\n", -42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---10---\n");
//        n = ft_printf(">%5.3d<\n", -42);
//        p = printf(">%5.3d<\n", -42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---11---\n");
//        n = ft_printf(">%+5.3d<\n", 42);
//        p = printf(">%+5.3d<\n", 42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---12---\n");
//        n = ft_printf(">%.3d<\n", 42);
//        p = printf(">%.3d<\n", 42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---13---\n");
//        n = ft_printf(">%+.3d<\n", 42);
//        p = printf(">%+.3d<\n", 42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---14---\n");
//        n = ft_printf(">%+.5d<\n", 42);
//        p = printf(">%+.5d<\n", 42);
//        if (n == p) printf("SUCCESS\n");
//        else {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---15---\n");
//        n = ft_printf(">% -6.4d<\n", 42);
//        p = printf(">% -6.4d<\n", 42);
//        if (n == p) printf("SUCCESS\n");
//        else
//        {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---16---\n");
//        n = ft_printf(">% -6.4d<\n", -42);
//        p = printf(">% -6.4d<\n", -42);
//        if (n == p) printf("SUCCESS\n");
//        else
//        {
//            printf("FAIL\n");
//            ft_printf("printed %d symbols in 1st line\n", n);
//            ft_printf("printed %d symbols in 2st line\n\n", p);
//        }
//		ft_printf("---17---\n");
//		n = ft_printf(">%d<\n", 2147483647);
//		p = printf(">%d<\n", 2147483647);
//		if (n == p) printf("SUCCESS\n");
//		else
//		{
//			printf("FAIL\n");
//			ft_printf("printed %d symbols in 1st line\n", n);
//			ft_printf("printed %d symbols in 2st line\n\n", p);
//		}
//		ft_printf("---18---\n");
//		n = ft_printf(">%ld<\n", -2147483648);
//		p = printf(">%ld<\n", -2147483648);
//		if (n == p) printf("SUCCESS\n");
//		else
//		{
//			printf("FAIL\n");
//			ft_printf("printed %d symbols in 1st line\n", n);
//			ft_printf("printed %d symbols in 2st line\n\n", p);
//		}
//		ft_printf("---19---\n");
//		n = ft_printf(">%ld<\n", -21474836489);
//		p = printf(">%ld<\n", -21474836489);
//		if (n == p) printf("SUCCESS\n");
//		else
//		{
//			printf("FAIL\n");
//			ft_printf("printed %d symbols in 1st line\n", n);
//			ft_printf("printed %d symbols in 2st line\n\n", p);
//		}
//		ft_printf("---20---\n");
//		n = ft_printf(">%lu<\n", -9223372036854775807);
//		p = printf(">%lu<\n", -9223372036854775807);
//		if (n == p) printf("SUCCESS\n");
//		else
//		{
//			printf("FAIL\n");
//			ft_printf("printed %d symbols in 1st line\n", n);
//			ft_printf("printed %d symbols in 2st line\n\n", p);
//		}
//		ft_printf("---20---\n");
//		n = ft_printf(">%llu<\n", 18446744073709551615);
//		p = printf(">%llu<\n", 18446744073709551615);
//		if (n == p) printf("SUCCESS\n");
//		else
//		{
//			printf("FAIL\n");
//			ft_printf("printed %d symbols in 1st line\n", n);
//			ft_printf("printed %d symbols in 2st line\n\n", p);
//		}
//		ft_printf("---21---\n");
//		n = ft_printf(">%-23.22lu<\n", 1844674407370955161);
//		p = printf(">%-23.22lu<\n", 1844674407370955161);
//		if (n == p) printf("SUCCESS\n");
//		else
//		{
//			printf("FAIL\n");
//			ft_printf("printed %d symbols in 1st line\n", n);
//			ft_printf("printed %d symbols in 2st line\n\n", p);
//		}
//		ft_printf("---22---\n");
//		n = ft_printf(">%5.d<\n", 0);
//		p = printf(">%5.d<\n", 0);
//		if (n == p) printf("SUCCESS\n");
//		else
//		{
//			printf("FAIL\n");
//			ft_printf("printed %d symbols in 1st line\n", n);
//			ft_printf("printed %d symbols in 2st line\n\n", p);
//		}
//		ft_printf("---23---\n");
//		n = ft_printf(">%5.0d<\n", 0);
//		p = printf(">%5.0d<\n", 0);
//		if (n == p) printf("SUCCESS\n");
//		else
//		{
//			printf("FAIL\n");
//			ft_printf("printed %d symbols in 1st line\n", n);
//			ft_printf("printed %d symbols in 2st line\n\n", p);
//		}
//		ft_printf("---24---\n");
//		n = ft_printf("> %.d %.0d<\n", 42, 43);
//		p = printf("> %.d %.0d<\n", 42,43);
//		if (n == p) printf("SUCCESS\n");
//		else
//		{
//			printf("FAIL\n");
//			ft_printf("printed %d symbols in 1st line\n", n);
//			ft_printf("printed %d symbols in 2st line\n\n", p);
//		}
		ft_printf("---25---\n");
		n = ft_printf(">%lld<\n", -9223372036854775808);
		p = printf(">%lld<\n", -9223372036854775808);
		if (n == p) printf("SUCCESS\n");
		else
		{
			printf("FAIL\n");
			ft_printf("printed %d symbols in 1st line\n", n);
			ft_printf("printed %d symbols in 2st line\n\n", p);
		}



//		uint64_t	tasks[] = {-9223372036854775807, 1844674407370955161, 0, 0, 0, 0, 1, 0};
//		char 		*exprs[] = {">%lu<\n", ">%llu<\n", ">%5.d<\n", ">%5.0d<\n", ">%02d<\n", ">%02.0d<\n", ">%03.2d<\n", ">%03.2d<\n"};
//
//
//		for (int i = 0; i < sizeof(tasks) / 8; i++)
//		{
//			ft_printf("---%02d---\n", i);
//			n = ft_printf(exprs[i], tasks[i]);
//			p = printf(exprs[i], tasks[i]);
//			if (n == p) printf("SUCCESS\n");
//		}
//		if (n == p) printf("SUCCESS\n");
//		else
//		{
//			printf("FAIL\n");
//			ft_printf("printed %d symbols in 1st line\n", n);
//			ft_printf("printed %d symbols in 2st line\n\n", p);
//		}
	}
	return (0);
}