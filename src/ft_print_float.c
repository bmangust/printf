/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/01/25 18:06:01 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_double *new_double(int is_double)
{
	t_double *num = (t_double*)malloc(sizeof(t_double));

	num->is_double = is_double;
	num->sign = ft_strnew(1);
	num->exp = NULL;
	num->mant = NULL;
	return (num);
}

t_double *get_bits(double d, float f, t_double *num)
{
	long long dl;
	int di;
	char *bits;
	int i;

	dl = *((long long*)&d);
	di = *((int*)&f);
	i = -1;
	bits = ft_strnew(64);
	if (num->is_double)
		while (++i < 64)
			bits[i] = ((dl >> (63 - i)) & 1) + '0';
	else
		while (++i < 32)
			bits[i] = ((di >> (31 - i)) & 1) + '0';
	num->sign[0] = bits[0];
	num->exp = ft_strsub(bits, 1, (num->is_double) ? 11 : 8);
	num->mant = (num->is_double) ? ft_strsub(bits, 12, 52)
								 : ft_strsub(bits, 9, 23);
	return (num);
}






/*

static long long int	float_base(double x)
{
	double			rest;
	int				e;
	long long int	base;

	e = -FLOAT_POWER;
	base = 0;
	while (e++ < FLOAT_POWER)
	{
		rest = x / ft_pow(2, e);
		if (rest >= 1 && rest < 2)
		{
			e += 1;
			break ;
		}
	}
	rest = x;
	while (rest > 0 && e-- > 0)
	{
		base += ft_pow(2, e);
		rest = x - base;
	}
		base += rest;
	return (base);
}

static void		lld_to_str(long long int integer, long long int	fract, t_parse *p)
{
	char	*str_int;
	char	*str_fract;
	char	*str;
	int		sign;

	sign = 0;
	(ft_strchr(p->flags, '+')) ? sign = 1 : sign;
	str_int = ft_ltoa(integer, (sign + 1));
	sign = 0;
	if (fract == 0 && p->precision != 0)
	{
		str_fract = ft_strnew((size_t) p->precision);
		while (p->precision-- > 0)
			str_fract[sign++] = '0';
	}
	else
		str_fract = ft_ltoa(fract, sign);
	str = ft_strjoin(str_int, str_fract);
	p->precision = 0;
	print_str(str, p);
	free(str_int);
	free(str_fract);
	free(str);
}

void	print_float(double valist, t_parse *p)
{
	long long int	integer;
	long long int	fract;

	if (!p->precision)
		p->precision = 6;
	integer = float_base(valist);
	fract = float_base((valist - integer) * ft_pow(10, p->precision + 1));
	(integer < 0 || valist < 0) ? fract *= -1 : fract;
	if (fract != 0)
		fract = (fract - 5)/10 + 1;
	lld_to_str(integer, fract, p);	
}
*/
