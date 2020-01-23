#include <limits.h>
#include <stdint.h>

int64_t ft_absint(int64_t n)
{
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