/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 01:59:00 by akraig            #+#    #+#             */
/*   Updated: 2020/01/22 16:11:23 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strappend(char const *src, char *dst, int start)
{
	int i;
	int j;

	i = 0;
	j = start;
	while (src[i])
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	return (j);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len;
	char	*s;

	i = 0;
	if (s1 != 0 && s2 != 0)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		s = (char*)malloc((len + 1) * sizeof(char));
		if (s)
		{
			i = ft_strappend(s1, s, 0);
			i = ft_strappend(s2, s, i);
			s[i] = '\0';
			return (s);
		}
	}
	return (NULL);
}
