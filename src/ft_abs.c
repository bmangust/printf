#include <limits.h>

int ft_absint(int n)
{
	    if (n == INT_MIN)
			        return (0);
		    if (n < 0)
				        return (-n);
			    return n;
}

float ft_absfloat(float f)
{
	    if (f < 0)
			        return (-f);
		    return (f);
}
