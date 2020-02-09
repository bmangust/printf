/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:01:32 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:02:05 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	params:
**	0 - length;
**	1 - point_position
**	2 - neg flag
*/

static int	*count_digits(long double d)
{
	int			*params;
	long long	tmp;

	params = (int*)malloc(sizeof(int) * 3);
	params[2] = d < 0 ? 1 : 0;
	params[0] = d < 0 ? 1 : 0;
	d < 0 ? d *= -1 : d;
	tmp = (long long)d;
	tmp == 0 ? params[0] += 1 : 0;
	while (tmp > 0 && ++params[0] > 0)
		tmp /= 10;
	params[1] = params[0];
	return (params);
}

char		*ft_dtoa(long double d)
{
	char	*s;
	int		*params;

	params = count_digits(d);
	d < 0 ? d *= -1 : d;
	while ((d - (long long)d) && ++params[0] < 22)
		d *= 10;
	s = ft_strnew(params[0] + 1);
	while (params[2] == 1 ? params[0] > 1 : params[0] > 0)
	{
		s[--params[0]] = (long long)d % 10 + '0';
		d /= 10;
		if (params[1] + 1 == params[0])
		{
			s[--params[0]] = '.';
			((int)d == 0) ? s[--params[0]] = '0' : 0;
		}
	}
	params[2] == 1 ? s[--params[0]] = '-' : 0;
	return (s);
}
