#include <limits.h>
#include <stdint.h>

__intmax_t ft_absint(__intmax_t n)
{
//    if (n == INT_MIN)
//        return (0);
    if (n < 0)
        return (-n);
    return n;
}

double ft_absfloat(double f)
{
    if (f < 0)
        return (-f);
    return (f);
}