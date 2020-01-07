#include "ft_printf.h"
#include "libft.h"

int main(int ac, char **av)
{
	// printf(">%4.3d<\tprintf\n", 42);
	int n, p;
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
		n = ft_printf(">%6.4i<\n", 45);
		p = printf(">%6.4i<\n", 45);
		ft_printf("printed %d symbols in 1st line\n", n);
		ft_printf("printed %d symbols in 2st line\n", p);
	}
	return (0);
}