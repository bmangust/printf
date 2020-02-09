/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:08:55 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:11:41 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_digits(int64_t n)
{
	int			cnt;

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

static void		ft_itoa_alg(int64_t n, char *s, int slen)
{
	int64_t		i;
	int64_t		cutter;

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

char			*ft_itoa(int64_t n)
{
	int			slen;
	char		*s;

	if (n == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	slen = count_digits(n);
	s = ft_strnew(slen);
	if (s)
	{
		ft_itoa_alg(n, s, slen);
		return (s);
	}
	return (NULL);
}

char			*ft_itoa_base(uint64_t value, uint64_t base)
{
	char		*snum;
	char		*s;
	uint64_t	val;
	size_t		cnt;

	val = value;
	cnt = 0;
	s = "0123456789abcdef";
	if (value == 0)
		return (ft_strdup("0"));
	while (value)
	{
		value /= base;
		cnt++;
	}
	if (!(snum = ft_strnew(cnt)))
		return (NULL);
	snum[cnt--] = '\0';
	while (val)
	{
		snum[cnt--] = s[val % base];
		val /= base;
	}
	return (snum);
}

char			*ft_itoa_baseu(uint64_t value, uint64_t base)
{
	char		*snum;
	char		*s;
	uint64_t	val;
	size_t		cnt;

	val = value;
	cnt = 0;
	s = "0123456789ABCDEF";
	if (value == 0)
		return (ft_strdup("0"));
	while (value)
	{
		value /= base;
		cnt++;
	}
	if (!(snum = ft_strnew(cnt)))
		return (NULL);
	snum[cnt--] = '\0';
	while (val)
	{
		snum[cnt--] = s[val % base];
		val /= base;
	}
	return (snum);
}
