/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:23:50 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 20:01:34 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_digits(long long int n)
{
	int cnt;

	if (n <= 0)
		cnt = 1;
	else
		cnt = 0;
	while (n)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

static void		ft_itoa_alg(long long int base, char *s, int slen, int sign)
{
	int				i;
	long long int	cutter;

	i = 0;
	if (sign > 1)
		s[i++] = '+';
	if (base < 0)
	{
		s[i++] = '-';
		base = -base;
	}
	while (i < slen + sign)
	{
		if (sign == 2)
			cutter = ft_pow(10, (slen - i - 0));
		else
			cutter = ft_pow(10, (slen - i - 1));
		s[i] = base / cutter + '0';
		base = base % cutter;
		i++;
	}
	if (sign > 0)
	{
		s[--i] = '.';
	}
}

char			*ft_ltoa(long long int base, int sign)
{
	int		slen;
	char	*s;

	slen = count_digits(base);
	s = ft_strnew((size_t)slen + sign);
	if (s)
	{
		ft_itoa_alg(base, s, slen, sign);
		return (s);
	}
	return (NULL);
}
