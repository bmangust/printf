/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 00:05:16 by akraig            #+#    #+#             */
/*   Updated: 2019/09/19 18:51:20 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
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

static void	ft_itoa_alg(int n, char *s, int slen)
{
	int i;
	int cutter;

	i = 0;
	if (n < 0)
	{
		s[i++] = '-';
		n = -n;
	}
	while (i < slen)
	{
		cutter = ft_pow(10, (slen - 1 - i));
		s[i] = n / cutter + '0';
		n = n % cutter;
		i++;
	}
	s[i] = '\0';
}

char		*ft_itoa(int n)
{
	int		slen;
	char	*s;

	if (n == -2147483648)
	{
		s = (char *)malloc(12 * sizeof(char));
		return (ft_strcpy(s, "-2147483648"));
	}
	slen = count_digits(n);
	s = (char *)malloc((slen + 1) * sizeof(char));
	if (s)
	{
		ft_itoa_alg(n, s, slen);
		return (s);
	}
	return (NULL);
}
