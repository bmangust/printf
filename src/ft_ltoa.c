/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:46:22 by jbloodax          #+#    #+#             */
/*   Updated: 2020/01/18 21:27:11 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long long int n)
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

static void	ft_itoa_alg(long long int n, char *s, int slen)
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

char		*ft_ltoa(long long int n)
{
	int		slen;
	char	*s;

	slen = count_digits((int) n);
	s = (char *)malloc((slen + 1) * sizeof(char));
	if (s)
	{
		ft_itoa_alg(n, s, slen);
		return (s);
	}
	return (NULL);
}
