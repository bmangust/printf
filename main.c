#include "ft_printf.h"
#include "libft.h"

int main(int ac, char **av)
{
	double d = 1234.56789;
	//float d = 0.124;
	t_double *num;
	num = new_double(d);
	num = get_bits(d, 0, num);
	// printf(">%4.3d<\tprintf\n", 42);
	//int n, p;
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
        // char *a;
        // a = "123545745.58";
		// ft_printf("---27---\n");
		// p = printf(">lib: %s<\n", "dfhsdffds");
		// n = ft_printf(">{ITALIC}our: %s{DEFAULT}<\n", "dfhsdffds");
		// if (n == p) printf("\nSUCCESS\n");
		// else
		// {
		// 	printf("FAIL\n");
		// 	ft_printf("printed %d symbols in 1st line\n", p);
		// 	ft_printf("printed %d symbols in 2st line\n\n", n);
		// }

		printf(">>dec num.exp: %lld\n", bin_to_dec(num->exp));
		printf(">>integer double: %s\n", integer_fl_d(num));
		printf(">>float orig: %lf\n", d);
		ft_printf(">>float ours: %lf\n", d);
		// printf(">>lib float: %f\n", d);
		




//		uint64_t	tasks[] = {2, 2, 0, 0, -9223372036854775807, 1844674407370955161, 0, 0, 0, 0, 1, 0};
//		char 		*exprs[] = {">%#.o<\n",  ">%#.0o<\n", ">%5.o<\n",  ">%5.0o<\n", ">%lu<\n", ">%llu<\n", ">%5.d<\n", ">%5.0d<\n", ">%02d<\n", ">%02.0d<\n", ">%03.2d<\n", ">%03.2d<\n"};
//
//
//		for (int i = 0; i < sizeof(tasks) / 8; i++)
//		{
//			ft_printf("---%02d---\n", i);
//			p = printf(exprs[i], tasks[i]);
//			n = ft_printf(exprs[i], tasks[i]);
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